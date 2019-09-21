cmake_minimum_required(VERSION 2.8)

project(LifeGame)

set(libs
   SDL2
   SDL2_ttf
)

set(HDR
    "src/constants.h"
    "src/field/field.h"
    "src/mechanic/mechanic.h"
    "src/renderer/renderer.h"
    )

set(SRC
    "src/field/field.c"
    "src/main.c"
    "src/mechanic/mechanic.c"
    "src/renderer/renderer.c"
)

add_compile_options(-fexceptions --std=c11 -Wall -O3)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} ${SRC} ${HDR})

target_link_libraries(${PROJECT_NAME} ${libs})
