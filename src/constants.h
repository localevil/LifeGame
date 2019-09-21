#pragma once
#include <stdint.h>

typedef enum state_t {
    STOP_GAME,
    CONTINUE_GAME,
    LIFE_PROCESSED
} state_t;

static const uint32_t BUTTON_WIDTH = 100, BUTTON_HEIGTH = 50;
static const uint32_t CELL_SIDE = 10;

static const uint32_t WIN_WIDTH = 940, WIN_HEIGHT = 560;
