cmake_minimum_required(VERSION 3.17)
project(Breakout)

set(CMAKE_CXX_STANDARD 20)

add_executable(Breakout WIN32
        main.cpp
        game/items/plate/Plate.cpp game/items/plate/Plate.h
        game/items/GameItem.cpp game/items/GameItem.h
        game/items/brick/Brick.cpp game/items/brick/Brick.h
        game/Game.cpp game/Game.h
        game/items/ball/Ball.cpp game/items/ball/Ball.h
        game/items/MovableGameItem.cpp game/items/MovableGameItem.h)
target_link_libraries(Breakout)