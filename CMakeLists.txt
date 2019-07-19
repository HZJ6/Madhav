cmake_minimum_required(VERSION 3.12)
project(Madhav)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(Madhav main.cpp Game.h Game.cpp)

target_link_libraries(Madhav ${SDL2_LIBRARY} -lmingw32 -lSDL2main -lSDL2)