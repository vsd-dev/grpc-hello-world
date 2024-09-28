// #include <iostream>
// #include <chrono>
// #include <string>
// #include "frame_rate_logger.h"

// FrameRateLogger::FrameRateLogger(double loggingFrequency, int batchSize)
//     : loggingFrequency_(loggingFrequency), batchSize_(batchSize), startTime(std::chrono::steady_clock::now()) {}

// FrameRateLogger::~FrameRateLogger() {}

// void FrameRateLogger::run(std::string tag, int writeReadDelay, bool logDelay) 
// {
//     batchCount_++;

//     // Calculate time duration in seconds since the last start time
//     auto now = std::chrono::steady_clock::now();
//     double timeDurationInSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count() / 1000.0;

//     // Check if it's time to log based on the logging frequency
//     if (timeDurationInSeconds >= loggingFrequency_)
//     {
//         // Calculate FPS
//         double fps = static_cast<double>(batchCount_ * batchSize_) / timeDurationInSeconds;

//         // Create log message
//         std::string logMessage = tag + " fps: " + std::to_string(fps);
//         if (logDelay)
//         {
//             logMessage += " (batch delay: " + std::to_string(writeReadDelay) + ")";
//         }

//         // Print the log message
//         std::cout << logMessage << std::endl;

//         // Reset the counters
//         batchCount_ = 0;

//         // Adjust startTime to account for the logging interval
//         startTime += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::milliseconds(static_cast<int>(loggingFrequency_ * 1000)));

//         // In case the logging frequency was missed by more than one interval
//         if (std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count() < 0) {
//             startTime = now;
//         }
//     }
// }


#include <iostream>
#include <chrono>
#include <string>
#include "frame_rate_logger.h"

// Constructor
FrameRateLogger::FrameRateLogger(double loggingFrequency, int batchSize, int averageCount)
    : loggingFrequency_(loggingFrequency), batchSize_(batchSize), averageCount_(averageCount), startTime(std::chrono::steady_clock::now()) {}

// Destructor
FrameRateLogger::~FrameRateLogger() {}

void FrameRateLogger::run(const std::string &tag, int writeReadDelay, bool logDelay)
{
    // Increment the batch count
    batchCount_++;

    // Calculate time duration in seconds since the last start time
    auto now = std::chrono::steady_clock::now();
    double timeDurationInSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count() / 1000.0;

    // Check if it's time to log based on the logging frequency
    if (timeDurationInSeconds >= loggingFrequency_)
    {
        // Calculate current FPS
        double fps = static_cast<double>(batchCount_ * batchSize_) / timeDurationInSeconds;

        // Accumulate the FPS for averaging
        fpsSum_ += fps;
        frameCount_++;

        // Check if we have enough counts to log average FPS
        if (frameCount_ >= averageCount_)
        {
            double averageFps = fpsSum_ / frameCount_;

            // Create log message with average FPS
            std::string logMessage = tag + " Average fps: " + std::to_string(averageFps);
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

        // Reset batch count and start time for the next interval
        batchCount_ = 0;
        startTime = std::chrono::steady_clock::now();
    }
}
