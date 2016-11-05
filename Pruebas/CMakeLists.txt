cmake_minimum_required(VERSION 3.6)
project(Pruebas)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES constants.h food.cpp food.h gamecontroller.cpp gamecontroller.h main.cpp mainwindow.cpp mainwindow.h
        snake.cpp snake.h wall.cpp wall.h)

find_package(Qt5Widgets REQUIRED)
add_executable(Pruebas ${SOURCE_FILES})

target_link_libraries(Pruebas Qt5::Widgets)