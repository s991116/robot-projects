#####################################
cmake_minimum_required (VERSION 2.8) 
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /usr/local/lib/cmake/)
project (FPSTest)
find_package(raspicam REQUIRED)
add_executable (FPSTest FPSTest.cpp)  
target_link_libraries (FPSTest ${raspicam_LIBS})
#####################################