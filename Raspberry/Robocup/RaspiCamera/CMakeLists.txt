cmake_minimum_required (VERSION 2.8)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /usr/local/lib/cmake/)
find_package(raspicam REQUIRED)
include_directories(${CMAKE_SOURCE_DIR}/RaspiCamera/include)
include_directories(${CMAKE_SOURCE_DIR}/RaspiCamCV/include)


file (GLOB ALL_SOURCE src/*.cpp)
add_library (RaspiCamera ${ALL_SOURCE})

target_link_libraries (RaspiCamera ${raspicam_LIBS} RaspiCamCV)
