cmake_minimum_required(VERSION 3.0.0)
project (Messaging)

# add the executable
add_library(Messaging msg.cpp)

#link MQTT library mosquitto
target_link_libraries(Messaging PUBLIC fastrtps)

# add the install targets
install (TARGETS Messaging 
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
