cmake_minimum_required(VERSION 3.2)

project(Game)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(SOURCES ${CMAKE_SOURCE_DIR}/src/game.cpp)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(${PROJECT_NAME} ${SOURCES})