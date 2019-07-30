cmake_minimum_required(VERSION 3.12)
project(Madhav)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})


add_executable(Madhav main.cpp Game.h Game.cpp Actor.h Component.h Actor.cpp Component.cpp Math.h Math.cpp CLASS_COMPONENT/SpriteComponent.h CLASS_COMPONENT/SpriteComponent.cpp CLASS_COMPONENT/BGSpriteComponent.h CLASS_COMPONENT/BGSpriteComponent.cpp CLASS_COMPONENT/AnimSpriteComponent.h CLASS_COMPONENT/AnimSpriteComponent.cpp CLASS_ACTOR/Ship.cpp CLASS_ACTOR/Ship.h CLASS_COMPONENT/TileMapComponent.h CLASS_COMPONENT/TileMapComponent.cpp CLASS_COMPONENT/MoveComponent.h CLASS_COMPONENT/MoveComponent.cpp Random.h Random.cpp CLASS_ACTOR/Asteroid.h CLASS_ACTOR/Asteroid.cpp CLASS_COMPONENT/InputComponent.h CLASS_COMPONENT/InputComponent.cpp CLASS_ACTOR/Laser.h CLASS_ACTOR/Laser.cpp CLASS_COMPONENT/CircleComponent.h CLASS_COMPONENT/CircleComponent.cpp)

target_link_libraries(Madhav ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})