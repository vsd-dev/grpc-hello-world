#ifndef FRAME_RATE_LOGGER_H
#define FRAME_RATE_LOGGER_H

#include <iostream>
#include <chrono>
#include <string>
#include <vector>

class FrameRateLogger {
public:
    /**
     * @brief Construct a new Frame Rate Logger object.
     * 
     * @param loggingFrequency Frequency (in seconds) at which to log the FPS.
     * @param batchSize Number of items per batch.
     * @param averageCount Number of counts over which to average FPS (default is 10).
     */
    FrameRateLogger(double loggingFrequency, int batchSize, int averageCount = 10);

    /**
     * @brief Destroy the Frame Rate Logger object.
     */
    ~FrameRateLogger();

    /**
     * @brief Runs the FPS logger.
     * 
     * @param tag A string tag to identify the log entry.
     * @param writeReadDelay Optional delay value (for logging purposes).
     * @param logDelay A flag indicating whether to log the delay.
     */
    void run(const std::string &tag, int writeReadDelay = 0, bool logDelay = false);

private:
    double loggingFrequency_;                            // Frequency in seconds to log FPS
    int batchSize_;                                      // Number of items per batch
    int batchCount_ = 0;                                 // Number of batches processed
    int totalBatchCount_ = 0;                            // Total number of batches processed
    int averageCount_;                                   // Number of counts over which to average FPS
    int frameCount_ = 0;                                 // Counter to track number of logged frames
    double fpsSum_ = 0.0;                                // Sum of FPS values for averaging
    std::chrono::steady_clock::time_point startTime;     // Start time for FPS calculation
    std::chrono::steady_clock::time_point lastLogTime;   // Last time the FPS was logged
};

#endif // FRAME_RATE_LOGGER_H
