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

add_executable(${PROJECT_NAME}
    ${SRC}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/inc
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        ASSETS_PATH="${ASSETS_PATH}"
)

find_package(raylib REQUIRED)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        ${COMPILE_WARNINGS}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        raylib
)

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/screenshots")


# Test
project(test)

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

find_package(raylib REQUIRED)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        raylib
)
