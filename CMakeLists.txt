cmake_minimum_required(VERSION 3.0.0)

## use this to globally use C++11 with in our project
set(CMAKE_CXX_STANDARD 11)

find_package( OpenCV REQUIRED )
find_package( fastcdr REQUIRED)
find_package( fastrtps REQUIRED)

add_subdirectory(src)
