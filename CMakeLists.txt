cmake_minimum_required(VERSION 3.1)
project(xyOpenCVOpenCL)

include_directories(${PROJECT_SOURCE_DIR})
message("PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")

add_subdirectory(src)
