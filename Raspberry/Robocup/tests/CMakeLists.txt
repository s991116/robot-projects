include_directories(${CMAKE_SOURCE_DIR}/Setting/include)
include_directories(${CMAKE_SOURCE_DIR}/StringUtil/include)
include_directories(${CMAKE_SOURCE_DIR}/tests/Setting)
include_directories(${CMAKE_SOURCE_DIR}/CommandScript/include)
include_directories(${CMAKE_SOURCE_DIR}/ArduinoController/include)
include_directories(${CMAKE_SOURCE_DIR}/Vision/include)

################################
# Unit Tests
################################
# Add test cpp file
add_executable( runUnitTests 
  Setting/SettingTest.cpp 
  Setting/SettingMock.cpp
  ParseCommandLine/ParseCommandLineTest.cpp
  StringUtil/Convert.cpp
  Vision/Position.cpp
)

# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests gtest gtest_main Setting CommandScript StringUtil Vision)

add_test( runUnitTests runUnitTests )