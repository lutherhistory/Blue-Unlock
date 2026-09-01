cmake_minimum_required(VERSION 3.16)

project(game
    VERSION 1.0
    LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(COMPILE_WARNINGS
    -Wall
    -Wextra
)

set(ASSETS_PATH "${CMAKE_SOURCE_DIR}/assets")

file(GLOB SRC "src/*.c")

find_package(raylib REQUIRED)

# Game
add_executable(game
    ${SRC}
)

target_include_directories(game
    PRIVATE
        ${CMAKE_SOURCE_DIR}/inc
)

target_compile_definitions(game
    PRIVATE
        ASSETS_PATH="${ASSETS_PATH}"
)

target_compile_options(game
    PRIVATE
        ${COMPILE_WARNINGS}
)

target_link_libraries(game
    PRIVATE
        raylib
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(game PRIVATE DEBUG)
endif()

# Test
add_executable(test
    test/main.test.c
    src/football-pitch.c
    src/football-referee.c
    src/physics-collisions.c
)

target_include_directories(test
    PRIVATE
        ${CMAKE_SOURCE_DIR}/inc
)

target_compile_definitions(test
    PRIVATE
        ASSETS_PATH="${ASSETS_PATH}"
)

target_compile_options(test
    PRIVATE
        ${COMPILE_WARNINGS}
)

target_link_libraries(test
    PRIVATE
        raylib
)

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/screenshots")
