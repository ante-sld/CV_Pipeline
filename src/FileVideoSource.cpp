//
// Created by antes on 14/01/2026.
//
#include "FileVideoSource.h"

Frame FileVideoSource::getFrame() {
    assert(m_cap.isOpened());
    cv::Mat image;
    m_cap >> image;
    Frame frame{image, m_frame_count++};
    return frame;
}

const int FileVideoSource::getFrameCount() {
    return m_frame_count;
}
