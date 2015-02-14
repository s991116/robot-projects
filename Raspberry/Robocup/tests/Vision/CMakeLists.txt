cmake_minimum_required (VERSION 2.8)

find_package( OpenCV REQUIRED )

include_directories(${CMAKE_SOURCE_DIR}/Vision/include)
include_directories(${CMAKE_SOURCE_DIR}/RaspiCamera/include)
include_directories(${CMAKE_SOURCE_DIR}/RaspiCamCV/include)
include_directories(${CMAKE_SOURCE_DIR}/Logging/include)
include_directories(${CMAKE_SOURCE_DIR}/tests/Vision/include)
include_directories( ${OpenCV_INCLUDE_DIRS} )

link_directories(~/git/robidouille/raspicam_cv)
link_directories(~/git/raspberrypi/userland/build/lib)

file (GLOB ALL_SOURCE src/*.cpp)
add_executable (VisionTest ${ALL_SOURCE})

target_link_libraries(VisionTest 
  Vision
  RaspiCamera
)
