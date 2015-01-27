cmake_minimum_required (VERSION 2.8)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /usr/local/lib/cmake/)
#find_package(raspicam REQUIRED)
find_package(raspicam)

include_directories(${CMAKE_SOURCE_DIR}/RaspiCamera/include)
include_directories(${CMAKE_SOURCE_DIR}/RaspiCamCV/include)
#link_directories(${CMAKE_SOURCE_DIR}/RaspiCamCV)
link_directories(~/git/robidouille/raspicam_cv)
link_directories(~/git/raspberrypi/userland/build/lib)

#file (GLOB ALL_SOURCE src/*.cpp)
file (GLOB ALL_SOURCE src/CameraDetectorMock.cpp)

add_library (RaspiCamera ${ALL_SOURCE})

#target_link_libraries (RaspiCamera ${raspicam_LIBS} raspicamcv mmal_core mmal mmal_util vcos bcm_host)
