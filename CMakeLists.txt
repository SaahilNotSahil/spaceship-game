cmake_minimum_required(VERSION 3.12)
project(spaceship-game)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

set(SOURCES
    src/asteroids.cpp
    src/background.cpp
    src/game.cpp
    src/main.cpp
    src/spaceship.cpp
    src/spacestation.cpp
    src/utils.cpp
)

set(HEADERS
    src/asteroids.h
    src/background.h
    src/constants.h
    src/game.h
    src/spaceship.h
    src/spacestation.h
    src/stb_image.h
    src/utils.h
)

add_executable(spaceship-game ${SOURCES} ${HEADERS})

target_link_libraries(spaceship-game
    GL
    GLU
    glut
)
