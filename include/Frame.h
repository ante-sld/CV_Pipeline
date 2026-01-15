//
// Created by antes on 14/01/2026.
//

#ifndef CV_PIPELINE_FRAME_H
#define CV_PIPELINE_FRAME_H

#include <opencv2/stitching/detail/util.hpp>

struct Frame {
    cv::Mat image{};
    uint frame_id{0};
    int64_t timestamp = cv::getTickCount();
};

#endif // CV_PIPELINE_FRAME_H