#include "include/file_reader.h"
#include "FileVideoSource.h"
#include "Frame.h"

#include <opencv2/opencv.hpp>
#include <spdlog/spdlog.h>
#include <rapidjson/document.h>

#include <iostream>
#include <string>


int main(int argc, const char * argv[]) {
    spdlog::info("Starting computer vision pipeline.");

    std::string configJson;
    read_file(argv[1], configJson);

    rapidjson::Document doc;
    doc.Parse(configJson.c_str());

    if (!doc.IsObject()) {
        std::cerr << "Error parsing config document. Check config argument." << std::endl;
        return 1;
    }

    FileVideoSource file_source(doc["source_path"].GetString());

    Frame frame{};
    while(true) {
        frame = file_source.getFrame();
        if(frame.image.empty()) break;  // end of video
        spdlog::info("Displaying frame number " + std::to_string(frame.frame_id) + " with timestamp " + std::to_string(frame.timestamp));
        cv::imshow("Video", frame.image);
        if(cv::waitKey(30) == 27) break; // ESC to exit
    }

    cv::destroyAllWindows();

    spdlog::info("Finishing computer vision pipeline.");
    return 0;
}