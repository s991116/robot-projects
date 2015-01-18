cmake_minimum_required (VERSION 2.8)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /usr/local/lib/cmake/)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include_directories(include)

project (Logging)
add_library (Logging ${ALL_SOURCE})

target_link_libraries(Logging StringUtil)