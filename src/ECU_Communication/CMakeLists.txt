cmake_minimum_required(VERSION 3.0.0)
project (ECU_Communication)

# add the executable
add_executable(ECU_Communication main.cpp)

#link MQTT library mosquitto
target_link_libraries(ECU_Communication PUBLIC Messaging ${OpenCV_LIBS})

# add the install targets
install (TARGETS ECU_Communication DESTINATION bin)
