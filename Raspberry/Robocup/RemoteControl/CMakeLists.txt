cmake_minimum_required (VERSION 2.8)

include_directories(${CMAKE_SOURCE_DIR}/RemoteControl/include) 
include_directories(${CMAKE_SOURCE_DIR}/Logging/include) 
include_directories(${CMAKE_SOURCE_DIR}/CommandScript/include) 
include_directories(${CMAKE_SOURCE_DIR}/Command/include) 
include_directories(${CMAKE_SOURCE_DIR}/Sensors/include)
include_directories(${CMAKE_SOURCE_DIR}/Setting/include)
include_directories(${CMAKE_SOURCE_DIR}/StringUtil/include)
include_directories(${CMAKE_SOURCE_DIR}/ArduinoController/include)
include_directories(${CMAKE_SOURCE_DIR}/Robot/include)

link_directories(~/git/robidouille/raspicam_cv)
link_directories(~/git/raspberrypi/userland/build/lib)

file (GLOB ALL_SOURCE src/*.cpp)
add_executable (RemoteControl ${ALL_SOURCE})

target_link_libraries(RemoteControl 
  Logging 
  CommandScript 
  Setting 
  Robot 
  Vision 
  Sensors 
  Command 
  ArduinoController 
  RaspiCamera
# raspicamcv mmal_core mmal mmal_util vcos bcm_host
  )

