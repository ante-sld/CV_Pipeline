//
// Created by antes on 14/01/2026.
//

#ifndef CV_PIPELINE_IVIDEOSOURCE_H
#define CV_PIPELINE_IVIDEOSOURCE_H
#include <opencv2/core/mat.hpp>
#include "Frame.h"

class IVideoSource {
public:
    IVideoSource(){}
    virtual ~IVideoSource(){}
    virtual Frame getFrame() = 0;
};

#endif //CV_PIPELINE_IVIDEOSOURCE_H