cmake_minimum_required(VERSION 3.0.0)
project (Image_Grabber)

# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/Config.h.in"
  "${PROJECT_BINARY_DIR}/Config.h"
  )

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")


## use this to globally use C++11 with in our project
set(CMAKE_CXX_STANDARD 11)

# add the executable
add_executable(Image_Grabber main.cpp)

#link amqpcpp, a RabbitMQ C++ client
target_link_libraries(Image_Grabber PUBLIC mosquitto)

# add the install targets
install (TARGETS Image_Grabber DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/Config.h"
         DESTINATION include)
