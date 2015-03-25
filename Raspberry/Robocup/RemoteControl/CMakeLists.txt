cmake_minimum_required (VERSION 2.8)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /usr/local/lib/cmake/)
if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

file (GLOB ALL_SOURCE src/*.cpp)

include_directories(${CMAKE_SOURCE_DIR}/RemoteControl/include) 
include_directories(${CMAKE_SOURCE_DIR}/Logging/include) 
include_directories(${CMAKE_SOURCE_DIR}/CommandScript/include) 
include_directories(${CMAKE_SOURCE_DIR}/Command/include) 
include_directories(${CMAKE_SOURCE_DIR}/Sensors/include)
include_directories(${CMAKE_SOURCE_DIR}/Setting/include)
include_directories(${CMAKE_SOURCE_DIR}/StringUtil/include)
include_directories(${CMAKE_SOURCE_DIR}/ArduinoController/include)
include_directories(${CMAKE_SOURCE_DIR}/Robot/include)

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
)