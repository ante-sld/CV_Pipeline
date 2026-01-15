cmake_minimum_required(VERSION 3.28)
project(CV_Pipeline LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- OpenCV ----
find_package(OpenCV REQUIRED CONFIG)

# ---- spdlog ----
find_package(spdlog REQUIRED CONFIG)

add_executable(cv_pipeline main.cpp
        src/file_reader.cpp
        include/Frame.h
        include/FixedQueue.h
        include/CaptureThread.h
        src/CaptureThread.cpp
        include/ProcessThread.h
        src/ProcessThread.cpp
        include/Const.h
)

target_include_directories(cv_pipeline
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(cv_pipeline
        PRIVATE
        opencv_core
        opencv_imgproc
        opencv_videoio
        opencv_imgcodecs
        opencv_highgui
        spdlog::spdlog
)

target_compile_options(cv_pipeline PRIVATE
        -Wno-deprecated-declarations
)