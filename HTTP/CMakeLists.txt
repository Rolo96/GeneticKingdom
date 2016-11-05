cmake_minimum_required(VERSION 3.6)
project(HTTP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(HTTP ${SOURCE_FILES})
target_link_libraries(HTTP /usr/local/lib/libcurl.a)