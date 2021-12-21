cmake_minimum_required(VERSION 3.6)
project(FlatBuffersParser)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH} ${CMAKE_HOME_DIRECTORY} ${CMAKE_HOME_DIRECTORY}/src")

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
include(CTest)

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
