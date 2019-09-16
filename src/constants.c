#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "field/field.h"

const uint32_t WIN_WIDTH = 960, WIN_HEIGHT = 540;

const uint32_t CELL_SIDE = 10;

const double FPS = 5.0;

const uint32_t BUTTON_WIDTH = 100, BUTTON_HEIGTH = 50;

const SDL_Rect START_STOP_BUTTON = {WIN_WIDTH - BUTTON_WIDTH, WIN_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGTH};
const SDL_Rect CLEAR_BUTTON = {0, WIN_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGTH};
