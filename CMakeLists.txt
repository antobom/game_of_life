cmake_minimum_required(VERSION 3.8)
project(Game_of_life)

set(OpenCV_DIR C:/Users/AntoineBAUMLER/Pictures/OpenCV/opencv-master/build)
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(main main.cpp)

target_link_libraries( main ${OpenCV_LIBS} )