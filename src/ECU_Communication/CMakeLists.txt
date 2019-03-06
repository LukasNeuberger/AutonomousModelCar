cmake_minimum_required(VERSION 3.0.0)
project (ECU_Communication)

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
add_executable(ECU_Communication main.cpp)

#link amqpcpp, a RabbitMQ C++ client
target_link_libraries(ECU_Communication PUBLIC mosquitto ${OpenCV_LIBS})

# add the install targets
install (TARGETS ECU_Communication DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/Config.h"
         DESTINATION include)
