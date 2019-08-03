cmake_minimum_required(VERSION 3.12)
project(Madhav)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})

add_executable(Madhav
        main.cpp
        Game.h
        Game.cpp
        Actor.h
        Actor.cpp
        Component.h
        CLASS_ACTOR/Bullet.cpp
        CLASS_ACTOR/Bullet.h
        CLASS_ACTOR/Enemy.cpp
        CLASS_ACTOR/Enemy.h
        CLASS_ACTOR/Grid.cpp
        CLASS_ACTOR/Grid.h
        CLASS_ACTOR/Tile.cpp
        CLASS_ACTOR/Tile.h
        CLASS_ACTOR/Tower.cpp
        CLASS_ACTOR/Tower.h
        Component.cpp
        Math.h
        Math.cpp
        CLASS_COMPONENT/SpriteComponent.h
        CLASS_COMPONENT/SpriteComponent.cpp
        CLASS_COMPONENT/MoveComponent.h
        CLASS_COMPONENT/MoveComponent.cpp
        CLASS_COMPONENT/NavComponent.h
        CLASS_COMPONENT/NavComponent.cpp
        Random.h
        Random.cpp
        CLASS_COMPONENT/CircleComponent.h
        CLASS_COMPONENT/CircleComponent.cpp
        CLASS_COMPONENT/AIComponent.h
        CLASS_COMPONENT/AIComponent.cpp
        CLASS_COMPONENT/AIState.h)

target_link_libraries(Madhav ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})