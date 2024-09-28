#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <atomic>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "inference.grpc.pb.h"
#include "answer_to_everything.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReaderWriter;
using grpc::Status;

ABSL_FLAG(int, frameRate, 4000, "The frame rate, with which the server processes (Hz)");

std::string GetServerAddress()
{
    const char *env_server_address = std::getenv("SERVER_ADDRESS");
    return env_server_address ? std::string(env_server_address) : "0.0.0.0:50051"; // Default address if not set
}

template <typename T>
class TSQueue
{
private:
    std::queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cond;

public:
    void push(T item)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(item);
        m_cond.notify_one();
    }

    T pop()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cond.wait(lock, [this]() { return !m_queue.empty(); });
        T item = m_queue.front();
        m_queue.pop();
        return item;
    }

    bool isEmpty()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }
};

void writeStream(ServerReaderWriter<inference::Response, inference::Request> *stream,
                 TSQueue<inference::Request> &batchQueue,
                 std::atomic<bool> &stop,
                 int frameRate)
{
    while (!stop.load(std::memory_order_relaxed) || !batchQueue.isEmpty())
    {
        inference::Request request = batchQueue.pop();
        if (request.image_data().empty())
        {
            std::cerr << "Error: Received empty image data!" << std::endl;
            continue;
        }

        inference::Response response;
        response.set_batch_index(request.batch_index());
        for (int i = 0; i < request.batch_size(); ++i)
        {
            response.add_classification(ANSWER_TO_EVERYTHING);
        }

        stream->Write(response);
    }
    std::cout << "Stream writer stopped." << std::endl;
}

class InferenceServiceImpl final : public inference::InferenceService::Service
{
private:
    int frameRate_ = 1;
    std::atomic<bool> shutdown_{false};

public:
    void SetFrameRate(int frameRate) { frameRate_ = frameRate; }
    bool IsShutdown() const { return shutdown_.load(std::memory_order_relaxed); }

    Status PredictBatch(ServerContext *context,
                        ServerReaderWriter<inference::Response, inference::Request> *stream) override
    {
        inference::Request request;
        while (stream->Read(&request))
        {
            if (request.image_data().empty())
            {
                std::cerr << "Error: Received empty image data!" << std::endl;
                continue;
            }

            inference::Response response;
            response.set_batch_index(request.batch_index());
            for (int i = 0; i < request.batch_size(); ++i)
            {
                response.add_classification(ANSWER_TO_EVERYTHING);
            }

            std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(1.0E6 * request.batch_size() / frameRate_)));
            stream->Write(response);
        }

        return Status::OK;
    }

    Status PredictBatchAsync(ServerContext *context,
                             ServerReaderWriter<inference::Response, inference::Request> *stream) override
    {
        TSQueue<inference::Request> batchQueue;
        std::atomic<bool> stop{false};
        std::thread writerThread(writeStream, stream, std::ref(batchQueue), std::ref(stop), frameRate_);

        inference::Request request;
        while (stream->Read(&request))
        {
            batchQueue.push(request);
        }

        stop.store(true, std::memory_order_relaxed);
        if (writerThread.joinable())
        {
            writerThread.join();
        }

        return Status::OK;
    }

    Status ShutdownServer(ServerContext *context,
                          const inference::Empty *request,
                          inference::Empty *response) override
    {
        shutdown_.store(true, std::memory_order_relaxed);
        return Status::OK;
    }
};

void RunServer(const std::string &serverAddress, int frameRate)
{
    InferenceServiceImpl service;
    service.SetFrameRate(frameRate);

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();

    int maxSize = 80 * 512 * 512 * 1;

    ServerBuilder builder;
    builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    builder.SetMaxSendMessageSize(maxSize);
    builder.SetMaxMessageSize(maxSize);
    builder.SetMaxReceiveMessageSize(maxSize);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << serverAddress << std::endl;

    std::thread serverShutdownThread([&service, &server]()
                                     {
        while (!service.IsShutdown())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::cout << "Shutting down server..." << std::endl;
        server->Shutdown(); });

    server->Wait();

    if (serverShutdownThread.joinable())
    {
        serverShutdownThread.join();
    }
}

int main(int argc, char **argv)
{
    absl::ParseCommandLine(argc, argv);
    std::string serverAddress = GetServerAddress();
    int frameRate = absl::GetFlag(FLAGS_frameRate);

    RunServer(serverAddress, frameRate);

    return 0;
}
