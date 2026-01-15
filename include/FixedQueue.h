//
// Created by antes on 15/01/2026.
//

#ifndef CV_PIPELINE_FIXEDQUEUE_H
#define CV_PIPELINE_FIXEDQUEUE_H
#include <queue>
#include <spdlog/spdlog.h>

#include "Frame.h"

template <int max> class FixedQueue {
  private:
    std::queue<Frame> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_c;

  public:
    FixedQueue() {}
    ~FixedQueue() {
        while (!m_queue.empty()) {
            m_queue.pop();
        }
    }
    void push(Frame frame) {

        std::unique_lock<std::mutex> lock(m_mutex);

        if (m_queue.size() == max) {
            Frame &droppedFrame = m_queue.front();
            spdlog::warn("Dropped frame with frame ID {}",
                         droppedFrame.frame_id);
            m_queue.pop();
        }
        m_queue.push(frame);

        m_c.notify_one();
    }

    Frame pop() {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_c.wait(lock, [this]() { return !m_queue.empty(); });

        Frame poppedFrame = m_queue.front();
        m_queue.pop();
        return poppedFrame;
    }

    size_t size() {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_queue.size();
    }

    Frame &front() {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_queue.front();
    }
};

#endif // CV_PIPELINE_FIXEDQUEUE_H