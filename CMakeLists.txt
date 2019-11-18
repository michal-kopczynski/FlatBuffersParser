cmake_minimum_required(VERSION 3.6)
project(FlatBuffersParser)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
include(CTest)
enable_testing()
add_subdirectory(test)
