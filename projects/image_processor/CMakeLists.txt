cmake_minimum_required(VERSION 3.16)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(image_processor
    image_processor.cpp
    parser.h
    parser.cpp
    bmp.h
    bmp.cpp
    filter.h
    filter.cpp
)
