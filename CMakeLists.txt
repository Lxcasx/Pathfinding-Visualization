cmake_minimum_required(VERSION 3.27)
project(Pathfinding)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

include(FetchContent)
FetchContent_Declare(plog
        GIT_REPOSITORY https://github.com/SergiusTheBest/plog.git
        GIT_TAG 1.1.10)
FetchContent_MakeAvailable(plog)
include_directories(${plog_SOURCE_DIR}/include)
add_compile_definitions(PLOG_ENABLE_WCHAR_INPUT)

add_executable(Pathfinding src/main.cpp
        src/Game.cpp
        src/Game.h
        src/engine/StateMachine.cpp
        src/engine/StateMachine.h
        src/engine/State.h
        src/engine/AssetManager.cpp
        src/engine/AssetManager.h
        src/engine/InputManager.cpp
        src/engine/InputManager.h
        src/DEFINITIONS.h
        src/states/SplashState.cpp
        src/states/SplashState.h
        src/states/MainState.cpp
        src/states/MainState.h
        src/states/GameState.cpp
        src/states/GameState.h
        src/Surface.cpp
        src/Surface.h
        src/Grid.h
        src/GridMap.cpp
        src/GridMap.h
        src/pathfinding/Pathfinding.h
        src/pathfinding/Pathfinding.cpp
        src/pathfinding/DijkstraFinding.cpp
        src/pathfinding/DijkstraFinding.h)


target_link_libraries(Pathfinding PRIVATE sfml-graphics)
target_link_libraries(Pathfinding PRIVATE sfml-audio)

install(TARGETS Pathfinding)

file(COPY resources DESTINATION ${CMAKE_BINARY_DIR}/bin)