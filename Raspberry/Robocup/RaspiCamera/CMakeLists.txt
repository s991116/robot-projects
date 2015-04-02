cmake_minimum_required (VERSION 2.8)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /usr/local/lib/cmake/)

if(${CMAKE_SYSTEM_PROCESSOR} MATCHES arm*) 
FIND_LIBRARY(mmalcore_LIBS NAMES mmal_core PATHS /opt/vc/lib)
FIND_LIBRARY(mmalutil_LIBS NAMES mmal_util PATHS /opt/vc/lib)
FIND_LIBRARY(mmal_LIBS NAMES mmal PATHS /opt/vc/lib)
IF( (NOT mmal_LIBS ) OR (NOT mmalutil_LIBS) OR (NOT mmalcore_LIBS) )
    MESSAGE(FATAL_ERROR "Could not find mmal libraries")
 ENDIF()
 set(REQUIRED_LIBRARIES ${REQUIRED_LIBRARIES} ${mmalcore_LIBS} ${mmalutil_LIBS} ${mmal_LIBS}  )
ENDIF()

LINK_LIBRARIES(raspicam ${REQUIRED_LIBRARIES})

#find_package(raspicam REQUIRED)
#link_directories("/usr/local/lib/")
MESSAGE( STATUS "Raspicam DIR:          ${raspicam_LIBS}" )
MESSAGE( STATUS "TEST")

include_directories(${CMAKE_SOURCE_DIR}/RaspiCamera/include)
include_directories(${CMAKE_SOURCE_DIR}/RaspiCamCV/include)
include_directories(${CMAKE_SOURCE_DIR}/ArduinoController/include)
include_directories(${CMAKE_SOURCE_DIR}/Logging/include)

if(CAMERA_MOCK)
    file (GLOB ALL_SOURCE src/PiCameraMock.cpp src/RobotCamera.cpp src/RobotCameraSetting.cpp)
else(CAMERA_MOCK)
    file (GLOB ALL_SOURCE src/PiCamera.cpp src/RobotCamera.cpp  src/RobotCameraSetting.cpp src/CameraNavigation.cpp src/CameraNavigationSetting.cpp)
endif(CAMERA_MOCK)

add_library (RaspiCamera ${ALL_SOURCE})

if(NOT CAMERA_MOCK)
    target_link_libraries (RaspiCamera ArduinoController raspicam_cv)
endif(CAMERA_MOCK)
