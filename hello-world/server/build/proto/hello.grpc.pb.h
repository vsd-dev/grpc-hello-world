// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: proto/hello.proto
#ifndef GRPC_proto_2fhello_2eproto__INCLUDED
#define GRPC_proto_2fhello_2eproto__INCLUDED

#include "proto/hello.pb.h"

#include <functional>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/proto_utils.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/stub_options.h>
#include <grpcpp/support/sync_stream.h>

namespace processing {

// Define the ProcessingServices service with a computeSum method
class ProcessingServices final {
 public:
  static constexpr char const* service_full_name() {
    return "processing.ProcessingServices";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    // Method to compute the sum of three numbers
    virtual ::grpc::Status computeSum(::grpc::ClientContext* context, const ::processing::Point3& request, ::processing::Numeric* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::processing::Numeric>> AsynccomputeSum(::grpc::ClientContext* context, const ::processing::Point3& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::processing::Numeric>>(AsynccomputeSumRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::processing::Numeric>> PrepareAsynccomputeSum(::grpc::ClientContext* context, const ::processing::Point3& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::processing::Numeric>>(PrepareAsynccomputeSumRaw(context, request, cq));
    }
    // Method to resize an image
    virtual ::grpc::Status resizeImage(::grpc::ClientContext* context, const ::processing::ImageRequest& request, ::processing::ImageResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::processing::ImageResponse>> AsyncresizeImage(::grpc::ClientContext* context, const ::processing::ImageRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::processing::ImageResponse>>(AsyncresizeImageRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::processing::ImageResponse>> PrepareAsyncresizeImage(::grpc::ClientContext* context, const ::processing::ImageRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::processing::ImageResponse>>(PrepareAsyncresizeImageRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      // Method to compute the sum of three numbers
      virtual void computeSum(::grpc::ClientContext* context, const ::processing::Point3* request, ::processing::Numeric* response, std::function<void(::grpc::Status)>) = 0;
      virtual void computeSum(::grpc::ClientContext* context, const ::processing::Point3* request, ::processing::Numeric* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      // Method to resize an image
      virtual void resizeImage(::grpc::ClientContext* context, const ::processing::ImageRequest* request, ::processing::ImageResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void resizeImage(::grpc::ClientContext* context, const ::processing::ImageRequest* request, ::processing::ImageResponse* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::processing::Numeric>* AsynccomputeSumRaw(::grpc::ClientContext* context, const ::processing::Point3& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::processing::Numeric>* PrepareAsynccomputeSumRaw(::grpc::ClientContext* context, const ::processing::Point3& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::processing::ImageResponse>* AsyncresizeImageRaw(::grpc::ClientContext* context, const ::processing::ImageRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::processing::ImageResponse>* PrepareAsyncresizeImageRaw(::grpc::ClientContext* context, const ::processing::ImageRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status computeSum(::grpc::ClientContext* context, const ::processing::Point3& request, ::processing::Numeric* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::processing::Numeric>> AsynccomputeSum(::grpc::ClientContext* context, const ::processing::Point3& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::processing::Numeric>>(AsynccomputeSumRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::processing::Numeric>> PrepareAsynccomputeSum(::grpc::ClientContext* context, const ::processing::Point3& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::processing::Numeric>>(PrepareAsynccomputeSumRaw(context, request, cq));
    }
    ::grpc::Status resizeImage(::grpc::ClientContext* context, const ::processing::ImageRequest& request, ::processing::ImageResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::processing::ImageResponse>> AsyncresizeImage(::grpc::ClientContext* context, const ::processing::ImageRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::processing::ImageResponse>>(AsyncresizeImageRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::processing::ImageResponse>> PrepareAsyncresizeImage(::grpc::ClientContext* context, const ::processing::ImageRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::processing::ImageResponse>>(PrepareAsyncresizeImageRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void computeSum(::grpc::ClientContext* context, const ::processing::Point3* request, ::processing::Numeric* response, std::function<void(::grpc::Status)>) override;
      void computeSum(::grpc::ClientContext* context, const ::processing::Point3* request, ::processing::Numeric* response, ::grpc::ClientUnaryReactor* reactor) override;
      void resizeImage(::grpc::ClientContext* context, const ::processing::ImageRequest* request, ::processing::ImageResponse* response, std::function<void(::grpc::Status)>) override;
      void resizeImage(::grpc::ClientContext* context, const ::processing::ImageRequest* request, ::processing::ImageResponse* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::processing::Numeric>* AsynccomputeSumRaw(::grpc::ClientContext* context, const ::processing::Point3& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::processing::Numeric>* PrepareAsynccomputeSumRaw(::grpc::ClientContext* context, const ::processing::Point3& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::processing::ImageResponse>* AsyncresizeImageRaw(::grpc::ClientContext* context, const ::processing::ImageRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::processing::ImageResponse>* PrepareAsyncresizeImageRaw(::grpc::ClientContext* context, const ::processing::ImageRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_computeSum_;
    const ::grpc::internal::RpcMethod rpcmethod_resizeImage_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    // Method to compute the sum of three numbers
    virtual ::grpc::Status computeSum(::grpc::ServerContext* context, const ::processing::Point3* request, ::processing::Numeric* response);
    // Method to resize an image
    virtual ::grpc::Status resizeImage(::grpc::ServerContext* context, const ::processing::ImageRequest* request, ::processing::ImageResponse* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_computeSum : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_computeSum() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_computeSum() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status computeSum(::grpc::ServerContext* /*context*/, const ::processing::Point3* /*request*/, ::processing::Numeric* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestcomputeSum(::grpc::ServerContext* context, ::processing::Point3* request, ::grpc::ServerAsyncResponseWriter< ::processing::Numeric>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_resizeImage : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_resizeImage() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_resizeImage() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status resizeImage(::grpc::ServerContext* /*context*/, const ::processing::ImageRequest* /*request*/, ::processing::ImageResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestresizeImage(::grpc::ServerContext* context, ::processing::ImageRequest* request, ::grpc::ServerAsyncResponseWriter< ::processing::ImageResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_computeSum<WithAsyncMethod_resizeImage<Service > > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_computeSum : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_computeSum() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::processing::Point3, ::processing::Numeric>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::processing::Point3* request, ::processing::Numeric* response) { return this->computeSum(context, request, response); }));}
    void SetMessageAllocatorFor_computeSum(
        ::grpc::MessageAllocator< ::processing::Point3, ::processing::Numeric>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::processing::Point3, ::processing::Numeric>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_computeSum() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status computeSum(::grpc::ServerContext* /*context*/, const ::processing::Point3* /*request*/, ::processing::Numeric* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* computeSum(
      ::grpc::CallbackServerContext* /*context*/, const ::processing::Point3* /*request*/, ::processing::Numeric* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithCallbackMethod_resizeImage : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_resizeImage() {
      ::grpc::Service::MarkMethodCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::processing::ImageRequest, ::processing::ImageResponse>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::processing::ImageRequest* request, ::processing::ImageResponse* response) { return this->resizeImage(context, request, response); }));}
    void SetMessageAllocatorFor_resizeImage(
        ::grpc::MessageAllocator< ::processing::ImageRequest, ::processing::ImageResponse>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(1);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::processing::ImageRequest, ::processing::ImageResponse>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_resizeImage() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status resizeImage(::grpc::ServerContext* /*context*/, const ::processing::ImageRequest* /*request*/, ::processing::ImageResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* resizeImage(
      ::grpc::CallbackServerContext* /*context*/, const ::processing::ImageRequest* /*request*/, ::processing::ImageResponse* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_computeSum<WithCallbackMethod_resizeImage<Service > > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_computeSum : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_computeSum() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_computeSum() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status computeSum(::grpc::ServerContext* /*context*/, const ::processing::Point3* /*request*/, ::processing::Numeric* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_resizeImage : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_resizeImage() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_resizeImage() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status resizeImage(::grpc::ServerContext* /*context*/, const ::processing::ImageRequest* /*request*/, ::processing::ImageResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_computeSum : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_computeSum() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_computeSum() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status computeSum(::grpc::ServerContext* /*context*/, const ::processing::Point3* /*request*/, ::processing::Numeric* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestcomputeSum(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_resizeImage : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_resizeImage() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_resizeImage() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status resizeImage(::grpc::ServerContext* /*context*/, const ::processing::ImageRequest* /*request*/, ::processing::ImageResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestresizeImage(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_computeSum : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_computeSum() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->computeSum(context, request, response); }));
    }
    ~WithRawCallbackMethod_computeSum() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status computeSum(::grpc::ServerContext* /*context*/, const ::processing::Point3* /*request*/, ::processing::Numeric* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* computeSum(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_resizeImage : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_resizeImage() {
      ::grpc::Service::MarkMethodRawCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->resizeImage(context, request, response); }));
    }
    ~WithRawCallbackMethod_resizeImage() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status resizeImage(::grpc::ServerContext* /*context*/, const ::processing::ImageRequest* /*request*/, ::processing::ImageResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* resizeImage(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_computeSum : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_computeSum() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::processing::Point3, ::processing::Numeric>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::processing::Point3, ::processing::Numeric>* streamer) {
                       return this->StreamedcomputeSum(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_computeSum() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status computeSum(::grpc::ServerContext* /*context*/, const ::processing::Point3* /*request*/, ::processing::Numeric* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedcomputeSum(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::processing::Point3,::processing::Numeric>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_resizeImage : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_resizeImage() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::StreamedUnaryHandler<
          ::processing::ImageRequest, ::processing::ImageResponse>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::processing::ImageRequest, ::processing::ImageResponse>* streamer) {
                       return this->StreamedresizeImage(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_resizeImage() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status resizeImage(::grpc::ServerContext* /*context*/, const ::processing::ImageRequest* /*request*/, ::processing::ImageResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedresizeImage(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::processing::ImageRequest,::processing::ImageResponse>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_computeSum<WithStreamedUnaryMethod_resizeImage<Service > > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_computeSum<WithStreamedUnaryMethod_resizeImage<Service > > StreamedService;
};

}  // namespace processing


#endif  // GRPC_proto_2fhello_2eproto__INCLUDED
