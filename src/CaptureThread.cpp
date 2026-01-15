//
// Created by antes on 15/01/2026.
//
#include "CaptureThread.h"

CaptureThread::CaptureThread(FixedQueue<Const::QUEUE_SIZE> &queue,
                             std::string_view file_path)
    : m_queue(queue),
      m_cap(cv::VideoCapture{static_cast<cv::String>(file_path)}),
      m_running(true) {
    if (!m_cap.isOpened()) {
        throw std::runtime_error("Failed to open video");
    }

    m_thread = std::thread(&CaptureThread::run, this);
}

CaptureThread::~CaptureThread() { stop(); }

void CaptureThread::stop() {
    m_running = false;
    if (m_thread.joinable()) {
        m_thread.join();
    }
}

void CaptureThread::waitForFinish() { m_thread.join(); }

void CaptureThread::run() {
    while (m_running) {
        cv::Mat image;
        m_cap >> image;
        if (image.empty()) {
            m_queue.push(Frame{});
            break; // Reached end of video
        }
        Frame frame{image, m_frame_count++};
        m_queue.push(frame);
        spdlog::info("[CAPTURE] Saved frame");
    }
}
