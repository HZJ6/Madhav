cmake_minimum_required(VERSION 3.12)
project(Madhav)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})


add_executable(Madhav main.cpp Game.h Game.cpp Actor.h Component.h Actor.cpp Component.cpp Math.h Math.cpp SpriteComponent.h SpriteComponent.cpp BGSpriteComponent.h BGSpriteComponent.cpp AnimSpriteComponent.h AnimSpriteComponent.cpp Ship.cpp Ship.h TileMapComponent.h TileMapComponent.cpp)

target_link_libraries(Madhav ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})