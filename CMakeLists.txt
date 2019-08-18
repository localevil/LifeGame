cmake_minimum_required(VERSION 2.8)

project(LifeGame)

set(libs
   SDL2
   SDL2_ttf
)

set(HDR
    "src/field/field.h"
    "src/mechanic/mechanic.h"
    "src/utils/utils.h"
    )

set(SRC
    "src/main.c"
    "src/field/field.c"
    "src/mechanic/mechanic.c"
    "src/utils/utils.c"
)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} ${SRC} ${HDR})

target_link_libraries(${PROJECT_NAME} ${libs})
