cmake_minimum_required(VERSION 3.0.0)
project (Messaging)

# add the executable
add_library(Messaging CamImage.cxx CamImagePublisher.cxx CamImageSubscriber.cxx CamImagePubSubTypes.cxx)

#link RTPS library fastrtps
target_link_libraries(Messaging PUBLIC fastcdr fastrtps)

# add the install targets
install (TARGETS Messaging 
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
