//
// Created by antes on 14/01/2026.
//

#ifndef CV_PIPELINE_FILEVIDEOSOURCE_H
#define CV_PIPELINE_FILEVIDEOSOURCE_H
#include "rapidjson/document.h"
#include "IVideoSource.h"
#include "Frame.h"
#include <opencv2/videoio.hpp>

class FileVideoSource : public IVideoSource {
private:
    cv::VideoCapture m_cap{};
    uint m_frame_count {};

public:
    FileVideoSource(std::string_view file_path)
        : m_cap(cv::VideoCapture{static_cast<cv::String>(file_path)})
    {
    }

    ~FileVideoSource() {
        m_cap.release();
    }
    Frame getFrame() override;
    const int getFrameCount();
};

#endif //CV_PIPELINE_FILEVIDEOSOURCE_H