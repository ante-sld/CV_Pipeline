cmake_minimum_required(VERSION 3.28.3)
project(CV_Pipeline)

set(CMAKE_CXX_STANDARD 20)

add_executable(CV_Pipeline main.cpp)

find_package(OpenCV REQUIRED)
target_link_libraries(CV_Pipeline PRIVATE ${OpenCV_LIBS})
include_directories(${OpenCV_INCLUDE_DIRS})