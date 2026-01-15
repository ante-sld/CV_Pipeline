#include "CaptureThread.h"
#include "FixedQueue.h"
#include "ProcessThread.h"
#include "file_reader.h"

#include <opencv2/opencv.hpp>
#include <rapidjson/document.h>
#include <spdlog/spdlog.h>

#include <iostream>
#include <string>

int main(int argc, const char *argv[]) {
    spdlog::info("Starting computer vision pipeline.");

    std::string configJson;
    read_file(argv[1], configJson);

    rapidjson::Document doc;
    doc.Parse(configJson.c_str());

    if (!doc.IsObject()) {
        std::cerr << "Error parsing config document. Check config argument."
                  << std::endl;
        return 1;
    }

    FixedQueue<Const::QUEUE_SIZE> frame_queue;
    // FileVideoSource file_source(frame_queue, doc["source_path"].GetString());
    CaptureThread capture(frame_queue, doc["source_path"].GetString());
    ProcessThread process(frame_queue);

    capture.waitForFinish();
    process.waitForFinish();

    cv::destroyAllWindows();

    spdlog::info("Finishing computer vision pipeline.");

    return 0;
}
