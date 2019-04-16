cmake_minimum_required(VERSION 3.0.0)
project (Image_Grabber)

# add the executable
add_executable(Image_Grabber main.cpp)

#link RTPS library fastrtps
target_link_libraries(Image_Grabber PUBLIC Messaging ${OpenCV_LIBS})

# add the install targets
install (TARGETS Image_Grabber DESTINATION bin)
