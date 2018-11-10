cmake_minimum_required(VERSION 2.8)
add_compile_options(-std=c++11)
project(subtitle_manipulate)

include_directories(./SubtitleManipulation/)
file(GLOB SOURCES "SubtitleManipulation/*.cpp" 
                    "SubtitleManipulation/app/impl/*.cpp")

add_executable(subtitle_manipulate ${SOURCES})