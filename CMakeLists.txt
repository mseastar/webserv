cmake_minimum_required(VERSION 3.21)
project(webserv_main)

set(CMAKE_CXX_STANDARD 11)

add_executable(webserv_main
        srcs/main.cpp
        srcs/Utils.cpp
        srcs/SimpSocket.cpp
        srcs/Server.cpp
        srcs/Request.cpp
        srcs/Config.cpp
        srcs/Response.cpp
        hdrs/Utils.hpp
        hdrs/Server.hpp
        hdrs/SimpSocket.hpp
        hdrs/Request.hpp
        hdrs/Config.hpp
        hdrs/ConfigParams.hpp
        hdrs/Response.hpp)
