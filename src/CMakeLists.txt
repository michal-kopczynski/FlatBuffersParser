#project(FlatBuffersParser)
set(CMAKE_VERBOSE_MAKEFILE ON)
message(STATUS "${CMAKE_BINARY_DIR}")
message(STATUS "${CMAKE_SOURCE_DIR}")

include(ExternalProject)

set(flatbuffers_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/flatbuffers)
ExternalProject_Add(
        flatbuffers
        PREFIX ${flatbuffers_PREFIX}
        URL "https://github.com/google/flatbuffers/archive/v1.10.0.tar.gz"
        URL_MD5 "f7d19a3f021d93422b0bc287d7148cd2"
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${flatbuffers_PREFIX} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        LOG_UPDATE ON
        LOG_CONFIGURE ON
        LOG_BUILD ON
)

set(FLATBUFFERS_LIBRARY ${flatbuffers_PREFIX}/lib/libflatbuffers.a)
set(FLATBUFFERS_GENERATOR ${flatbuffers_PREFIX}/bin/flatc)

message(STATUS "${flatbuffers_PREFIX}")
message(STATUS "${flatbuffers_PREFIX}/include")
message(STATUS "${FLATBUFFERS_LIBRARY}")
message(STATUS "${FLATBUFFERS_GENERATOR}")
include_directories(${flatbuffers_PREFIX}/include)
#include_directories(${flatbuffers_source_dir}/include)
add_library(Client Client.cpp Client.hpp)
add_library(Socket Socket.cpp Socket.hpp)
add_library(Parser Parser.cpp Parser.hpp)
add_executable(FlatBuffersParser main.cpp)
add_dependencies(FlatBuffersParser flatbuffers)

target_link_libraries(FlatBuffersParser Client Socket Parser ${FLATBUFFERS_LIBRARY} pthread)
#set(LINK_LIBRARIES
#    ${Socket}
#    ${Parser}
#    ${flatbuffers}
#    ${Abc}
#    ${pthread}
#)
#target_link_libraries(FlatBuffersParser ${LINK_LIBRARIES})

add_custom_command(
        TARGET FlatBuffersParser POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/src/FlatBuffersParser
        ${CMAKE_SOURCE_DIR}/bin/FlatBuffersParser)


#target_link_libraries(FlatbuffersRESTfulParser PRIVATE cpprestsdk::cpprest)

#target_include_directories(FlatbuffersRESTfulParser PUBLIC
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/flatbuffers>
#        $<INSTALL_INTERFACE:flatbuffers>  # <prefix>/include/mylib
#        )