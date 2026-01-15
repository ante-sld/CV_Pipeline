//
// Created by antes on 15/01/2026.
//

#ifndef CV_PIPELINE_PROCESSTHREAD_H
#define CV_PIPELINE_PROCESSTHREAD_H
#include "Const.h"
#include "FixedQueue.h"
#include <thread>

class ProcessThread {
  public:
    ProcessThread(FixedQueue<Const::QUEUE_SIZE> &queue);
    ~ProcessThread();

    void stop();
    void waitForFinish();

  private:
    void run();

    std::thread m_thread;
    FixedQueue<Const::QUEUE_SIZE> &m_queue;
    bool m_running{false};
};

#endif // CV_PIPELINE_PROCESSTHREAD_H