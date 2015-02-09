cmake_minimum_required (VERSION 2.8)

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

file (GLOB ALL_SOURCE src/Template.cpp)
add_executable (OpenCVFastTemplate ${ALL_SOURCE})

target_link_libraries(OpenCVFastTemplate ${OpenCV_LIBS})
