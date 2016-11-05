cmake_minimum_required(VERSION 3.6)
project(GeneticKingdom)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES com.GeneticKingdom.Main/main.cpp com.GeneticKingdom.EstructurasDatos/Array.cpp com.GeneticKingdom.EstructurasDatos/Array.h com.GeneticKingdom.Logica/bala.cpp com.GeneticKingdom.Logica/bala.h com.GeneticKingdom.Logica/enemigo.h com.GeneticKingdom.Logica/enemigo.cpp com.GeneticKingdom.UI/juego.cpp com.GeneticKingdom.UI/juego.h
        com.GeneticKingdom.EstructurasDatos/List.h com.GeneticKingdom.EstructurasDatos/List.cpp com.GeneticKingdom.Logica/Pathfinding.h com.GeneticKingdom.Logica/Pathfinding.cpp com.GeneticKingdom.EstructurasDatos/Node.h com.GeneticKingdom.EstructurasDatos/Node.cpp com.GeneticKingdom.Logica/tower.h com.GeneticKingdom.Logica/tower.cpp)
add_executable(GeneticKingdom ${SOURCE_FILES})

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
target_link_libraries(GeneticKingdom /usr/local/lib/libcurl.a)
target_link_libraries(GeneticKingdom /usr/lib/libjson_linux-gcc-5.4.0_libmt.so)
target_link_libraries(GeneticKingdom Qt5::Widgets)
target_link_libraries(GeneticKingdom Qt5::Multimedia)

