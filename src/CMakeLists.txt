cmake_minimum_required(VERSION 2.8)
project(subtitle_manipulate)

include_directories(./)
file(GLOB SOURCES "*.cpp" 
                    "app/*.cpp")
add_executable(subtitle_manipulate ${SOURCES})