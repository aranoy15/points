cmake_minimum_required(VERSION 3.10.0)

set(PROJECT pointtestproject)
project(${PROJECT} CXX)

set(TARGET ${PROJECT})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Weffc++")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(${TARGET} main.cpp)

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(library)
add_subdirectory(window)

target_link_libraries(${TARGET} Qt5::Widgets)