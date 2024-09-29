#include <iostream>
#include <chrono>
#include <string>
#include "frame_rate_logger.h"

// Constructor
FrameRateLogger::FrameRateLogger(double loggingFrequency, int batchSize, int averageCount)
    : loggingFrequency_(loggingFrequency), batchSize_(batchSize), averageCount_(averageCount), startTime(std::chrono::steady_clock::now()), lastLogTime(std::chrono::steady_clock::now())
{
    std::cout << "FrameRateLogger initialized with loggingFrequency: " << loggingFrequency_ << ", batchSize: " << batchSize_ << ", averageCount: " << averageCount_ << std::endl;
}

void FrameRateLogger::run(const std::string &tag, int writeReadDelay, bool logDelay)
{
    // std::cout << "Inside frame logger" << std::endl; // Debug print

    // Increment both the interval-specific and total batch counts
    batchCount_++;
    totalBatchCount_++;
    // Calculate time duration in seconds since the last log time
    auto now = std::chrono::steady_clock::now();
    double timeDurationInSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastLogTime).count() / 1000.0;

    // Debug prints to trace the current state
    // std::cout << "Time duration since last log: " << timeDurationInSeconds << " seconds, Logging frequency: " << loggingFrequency_ << std::endl;
    // std::cout << "Batc   h count: " << batchCount_ << ", Frame count: " << frameCount_ << std::endl;

    // Check if it's time to log based on the logging frequency
    if (timeDurationInSeconds >= loggingFrequency_)
    {
        // Calculate current FPS based on time since startTime
        double fps = static_cast<double>(batchCount_ * batchSize_) / timeDurationInSeconds;
        std::cout << "Current FPS: " << fps << std::endl; // Debug print for FPS
        // Accumulate the FPS for averaging
        fpsSum_ += fps;
        frameCount_++;

        // Check if we have enough counts to log average FPS
        if (frameCount_ >= averageCount_)
        {
            double averageFps = fpsSum_ / frameCount_;
            // Calculate Batches Per Second (BPS)
            double averageBatchesPerSecond = static_cast<double>(totalBatchCount_) / (std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count());
            // Create log message with average FPS
            std::string logMessage = tag + " Average fps: " + std::to_string(averageFps) + 
                                     ", Average Batches Per Second: " + std::to_string(averageBatchesPerSecond);
            logMessage += " | Total processed batches: " + std::to_string(totalBatchCount_);
            if (logDelay)
            {
                logMessage += " (batch delay: " + std::to_string(writeReadDelay) + ")";
            }

            // Print the log message
            std::cout << logMessage << std::endl;

            // Reset the FPS accumulation and frame count after logging
            fpsSum_ = 0.0;
            frameCount_ = 0;
        }

        // Update last log time
        lastLogTime = now;
        batchCount_ = 0;
    }
}
FrameRateLogger::~FrameRateLogger()
{
    // Print the total number of batches processed when the object is destroyed
    std::cout << "Total processed batches (final): " << totalBatchCount_ << std::endl;
}