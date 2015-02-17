cmake_minimum_required (VERSION 2.8)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /usr/local/lib/cmake/)

find_package(raspicam)

include_directories(${CMAKE_SOURCE_DIR}/RaspiCamera/include)
include_directories(${CMAKE_SOURCE_DIR}/RaspiCamCV/include)
include_directories(${CMAKE_SOURCE_DIR}/ArduinoController/include)

link_directories(~/git/robidouille/raspicam_cv)
link_directories(~/git/raspberrypi/userland/build/lib)

if(CAMERA_MOCK)
    file (GLOB ALL_SOURCE src/CameraDetectorMock.cpp)
else(CAMERA_MOCK)
    file (GLOB ALL_SOURCE src/CameraDetector.cpp)
endif(CAMERA_MOCK)

add_library (RaspiCamera ${ALL_SOURCE})

if(NOT CAMERA_MOCK)
    target_link_libraries (RaspiCamera ${raspicam_LIBS} ArduinoController raspicamcv mmal_core mmal mmal_util vcos bcm_host)
endif(CAMERA_MOCK)
