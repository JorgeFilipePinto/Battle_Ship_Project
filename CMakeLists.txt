cmake_minimum_required(VERSION 3.26)
project(Battle_Ship)

set(CMAKE_CXX_STANDARD 17)

add_executable(Battle_Ship BattleShip.cpp
        Boat.cpp
        Boat.h
        Map.cpp
        Map.h
        Player.cpp
        Player.h)
