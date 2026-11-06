cmake_minimum_required(VERSION 3.15)
project(BattleGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(BattleGame
    src/main.cpp
    src/entities/Entity.cpp
    src/entities/Support.cpp
    src/entities/Mage.cpp
    src/entities/Knight.cpp
    src/entities/Archer.cpp
    src/entities/Berserker.cpp
    src/entities/Hunter.cpp
    src/entities/Monster.cpp
    src/Progression.cpp
    src/HeroRoster.cpp
)

target_include_directories(BattleGame PRIVATE src src/entities)
