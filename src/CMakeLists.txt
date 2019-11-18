set(CMAKE_VERBOSE_MAKEFILE ON)
include(ExternalProject)

# flatbuffers
set(flatbuffers_PATH ${CMAKE_CURRENT_BINARY_DIR}/external/flatbuffers)
ExternalProject_Add(
        flatbuffers
        PREFIX ${flatbuffers_PATH}
        URL "https://github.com/google/flatbuffers/archive/v1.10.0.tar.gz"
        URL_MD5 "f7d19a3f021d93422b0bc287d7148cd2"
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${flatbuffers_PATH} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        LOG_UPDATE ON
        LOG_CONFIGURE ON
        LOG_BUILD ON
)

set(FLATBUFFERS_LIBRARY ${flatbuffers_PATH}/lib/libflatbuffers.a)
set(FLATBUFFERS_GENERATOR ${flatbuffers_PATH}/bin/flatc)
include_directories(${flatbuffers_PATH}/include)

# cxxopts
set(cxxopts_PATH ${CMAKE_CURRENT_BINARY_DIR}/external/cxxopts)
ExternalProject_Add(
        cxxopts
        PREFIX ${cxxopts_PATH}
        URL "https://github.com/jarro2783/cxxopts/archive/v2.2.0.tar.gz"
        URL_MD5 "d6d1582645e5c17d04bcdc769326c8a5"
        CONFIGURE_COMMAND ""
        INSTALL_COMMAND ""
        BUILD_COMMAND ""
        LOG_DOWNLOAD ON
        )

ExternalProject_Get_Property(cxxopts source_dir)
set(CXXOPTS_INCLUDE_PATH ${source_dir}/include)

add_library(Client Client.cpp Client.hpp)
add_library(Socket Socket.cpp Socket.hpp)
add_library(Parser Parser.cpp Parser.hpp)
add_executable(FlatBuffersParser main.cpp ${CXXOPTS_INCLUDE_PATH}/cxxopts.hpp)
target_include_directories(FlatBuffersParser PRIVATE ${CXXOPTS_INCLUDE_PATH})

target_link_libraries(FlatBuffersParser Client Socket Parser ${FLATBUFFERS_LIBRARY} pthread)

# add_dependencies(FlatBuffersParser flatbuffers cxxopts)

add_custom_command(
        TARGET FlatBuffersParser POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/src/FlatBuffersParser
        ${CMAKE_SOURCE_DIR}/bin/FlatBuffersParser)
        