find_package(OpenCV REQUIRED)
#find_package(OpenCL REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(xy main.cpp threads.cpp opencv-opencl.cpp)
target_link_libraries(xy ${OpenCV_LIBS})
