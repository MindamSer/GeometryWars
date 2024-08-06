
# You are free to modify this file

project(Geometry-Wars)

cmake_minimum_required(VERSION 3.0)
find_package(X11 REQUIRED)

set(CMAKE_CONFIGURATION_TYPES "Debug" "Release")
include_directories(./include)
file(GLOB SRC Engine.cpp)
file(GLOB ENT entities/*.cpp)
file(GLOB GEO geometry/*.cpp)
file(GLOB UTI utils/*.cpp)

add_executable(game ${SRC} ${ENT} ${GEO} ${UTI})
target_link_libraries(game m X11)
