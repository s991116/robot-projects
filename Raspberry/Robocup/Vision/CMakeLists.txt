cmake_minimum_required (VERSION 2.8)

get_cmake_property(_variableNames VARIABLES)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()


find_package( OpenCV REQUIRED )

include_directories(${CMAKE_SOURCE_DIR}/Vision/include)
include_directories(${CMAKE_SOURCE_DIR}/RaspiCamera/include)
include_directories(${CMAKE_SOURCE_DIR}/RaspiCamCV/include)
include_directories(${CMAKE_SOURCE_DIR}/Logging/include)
include_directories(${CMAKE_SOURCE_DIR}/Setting/include)
include_directories(${CMAKE_SOURCE_DIR}/StringUtil/include)
include_directories(${CMAKE_SOURCE_DIR}/ArduinoController/include)
include_directories( ${OpenCV_INCLUDE_DIRS} )

file (GLOB ALL_SOURCE src/*.cpp)
add_library (Vision ${ALL_SOURCE})

target_link_libraries(Vision Logging ${OpenCV_LIBS})
