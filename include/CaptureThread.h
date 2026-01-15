//
// Created by antes on 15/01/2026.
//

#ifndef CV_PIPELINE_CAPTURETHREAD_H
#define CV_PIPELINE_CAPTURETHREAD_H

#include "Const.h"
#include "FixedQueue.h"

#include <opencv2/videoio.hpp>
#include <thread>

class CaptureThread {
  public:
    CaptureThread(FixedQueue<Const::QUEUE_SIZE> &queue,
                  std::string_view file_path);
    ~CaptureThread();

    void stop();
    void waitForFinish();

  private:
    void run();

    std::thread m_thread;
    FixedQueue<Const::QUEUE_SIZE> &m_queue;
    cv::VideoCapture m_cap;
    uint m_frame_count{};
    bool m_running{false};
};

#endif // CV_PIPELINE_CAPTURETHREAD_H