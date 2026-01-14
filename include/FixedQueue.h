//
// Created by antes on 15/01/2026.
//

#ifndef CV_PIPELINE_FIXEDQUEUE_H
#define CV_PIPELINE_FIXEDQUEUE_H
#include <deque>
#include <opencv2/core/mat.hpp>
#include <spdlog/spdlog.h>

#include "Frame.h"

template<int max>
class FixedQueue {
private:
    std::deque<Frame> queue;
public:
    void push(Frame& frame) {
        if (queue.size() == max) {
            Frame& droppedFrame = queue.front();
            spdlog::error("Dropped frame with frame ID " + std::to_string(droppedFrame.frame_id));
            queue.pop_front();
        }
        queue.push_back(frame);
    }
};

#endif //CV_PIPELINE_FIXEDQUEUE_H