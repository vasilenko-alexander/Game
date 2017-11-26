cmake_minimum_required(VERSION 3.2)

project(Game)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(INCLUDES ${CMAKE_SOURCE_DIR}/include)
set(PROJECT_LIBS_DIR ${CMAKE_SOURCE_DIR}/lib)

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

include_directories(${INCLUDES})

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(PROJECT_LINK_LIB -lSDL2d)
else(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(PROJECT_LINK_LIB -lSDL2)
endif()

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

link_directories(${PROJECT_LIBS_DIR})
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${PROJECT_LINK_LIB})