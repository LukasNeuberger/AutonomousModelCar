cmake_minimum_required(VERSION 3.13)
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
message("PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")


# add ZMQ for message queueing
set (EXTRA_LIBS ${EXTRA_LIBS} ZeroMQ)

# add the executable
add_executable(ECU_Communication main.cpp)
target_link_libraries (ECU_Communication  ${EXTRA_LIBS})

# add the install targets
install (TARGETS ECU_Communication DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/Config.h"        
         DESTINATION include)
