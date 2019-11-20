set(CMAKE_VERBOSE_MAKEFILE ON)
include(ExternalProject)

# flatbuffers
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

# cxxopts
set(cxxopts_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/cxxopts)
ExternalProject_Add(
        cxxopts
        PREFIX ${cxxopts_PREFIX}
        URL "https://github.com/jarro2783/cxxopts/archive/v2.2.0.tar.gz"
        URL_MD5 "d6d1582645e5c17d04bcdc769326c8a5"
        CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${cxxopts_PREFIX}
        LOG_UPDATE ON
        LOG_BUILD ON
        LOG_INSTALL ON
        )

ExternalProject_Get_Property(cxxopts source_dir)
set(CXXOPTS_INCLUDE_PATH ${source_dir}/include)

# Boost
include(boost)

add_subdirectory(server)

# message(STATUS "Boost_INCLUDE_DIRS:" ${Boost_INCLUDE_DIRS})

add_library(Arguments Arguments.cpp)
add_dependencies(Arguments cxxopts)
target_include_directories(Arguments PRIVATE ${CXXOPTS_INCLUDE_PATH})

add_library(Socket Socket.cpp)

add_library(WebsocketHandler WebsocketHandler.cpp)

add_library(Parser Parser.cpp)
add_dependencies(Parser flatbuffers)
target_include_directories(Parser PRIVATE ${flatbuffers_PREFIX}/include)# ${Boost_INCLUDE_DIRS})
#target_link_libraries(Parser PRIVATE Boost::beast)

add_executable(FlatBuffersParser main.cpp)
target_link_libraries(FlatBuffersParser Arguments Parser WebsocketHandler Server ${FLATBUFFERS_LIBRARY} pthread boost::beast)

add_custom_command(
        TARGET FlatBuffersParser POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/src/FlatBuffersParser
        ${CMAKE_SOURCE_DIR}/bin/FlatBuffersParser)
        