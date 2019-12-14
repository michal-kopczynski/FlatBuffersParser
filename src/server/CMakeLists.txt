cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(server)

include(CMakeFindDependencyMacro)

find_dependency(unofficial-http-parser)
find_dependency(fmt REQUIRED)
find_dependency(restinio CONFIG REQUIRED) 


add_library(HttpRouter 
        HttpRouter.cpp
        HttpRouter.hpp
        )
target_link_libraries(HttpRouter PUBLIC restinio::restinio)

add_library(Server 
        Server.cpp
        Server.hpp
        )
target_link_libraries(Server PUBLIC restinio::restinio HttpRouter)
