cmake_minimum_required(VERSION 3.17)
project(rtsp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(OpenCV REQUIRED)
set(CMAKE_CXX_STANDARD 14)

add_executable(rtsp main.cpp)
target_link_libraries(rtsp ${OpenCV_LIBS})