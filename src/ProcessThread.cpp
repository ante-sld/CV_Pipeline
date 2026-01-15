//
// Created by antes on 15/01/2026.
//

#include "ProcessThread.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

ProcessThread::ProcessThread(FixedQueue<Const::QUEUE_SIZE> &queue)
    : m_queue(queue), m_running(true) {
    m_thread = std::thread(&ProcessThread::run, this);
}

ProcessThread::~ProcessThread() { stop(); }

void ProcessThread::stop() {
    m_running = false;
    if (m_thread.joinable()) {
        m_thread.join();
    }
}

void ProcessThread::waitForFinish() { m_thread.join(); }

void ProcessThread::run() {
    while (m_running) {
        Frame frame = m_queue.pop();
        if (frame.image.empty())
            break; // end of video
        spdlog::info("Displaying frame number " +
                     std::to_string(frame.frame_id) + " with timestamp " +
                     std::to_string(frame.timestamp));
        cv::cvtColor(frame.image, frame.image, cv::COLOR_BGR2GRAY);
        cv::imshow("Video", frame.image);
        if (cv::waitKey(30) == 27) {
            break;
        }
    }
}