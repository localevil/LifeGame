#include "renderer.h"

#include <assert.h>
#include <SDL2/SDL.h>
#include "../constants.c"

static SDL_Window* window;
static SDL_Renderer* renderer;

static SDL_Texture* START_TEXTURE;
static SDL_Texture* STOP_TEXTURE;
static SDL_Texture* CLEAR_TEXTURE;

const uint32_t CELL_SIDE = 10;
const double FPS = 5.0;

const SDL_Rect START_STOP_BUTTON = {WIN_WIDTH - BUTTON_WIDTH, WIN_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGTH};
const SDL_Rect CLEAR_BUTTON = {0, WIN_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGTH};

void initRenderer(Field *field)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    
    window = SDL_CreateWindow("Window", 1,0, (int32_t)getWidth(field), (int32_t)(getHeight(field) + BUTTON_HEIGTH), SDL_WINDOW_SHOWN);
    assert(window != NULL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    assert(renderer != NULL);
    
    const char* START_TEXT = "Start";
    const char* STOP_TEXT = "Stop";
    const char* CLEAR_TEXT = "Clear";
    
    START_TEXTURE = createTextTexture(renderer, START_TEXT);
    STOP_TEXTURE  = createTextTexture(renderer, STOP_TEXT);
    CLEAR_TEXTURE = createTextTexture(renderer, CLEAR_TEXT);
}

void deleteRenderer()
{
    SDL_DestroyRenderer(renderer);
    assert(renderer == NULL);
    SDL_DestroyWindow(window);
    assert(window == NULL);
    
}

void drawElement(Field* field, uint32_t i, uint32_t j) {
    if (*fieldElm(field, i, j) > 0) {
        SDL_Rect rect = {(int32_t)(i * CELL_SIDE), (int32_t)(j * CELL_SIDE), (int32_t)(CELL_SIDE), (int32_t)(CELL_SIDE)};
        SDL_RenderFillRect(renderer, &rect);
    }
}

static endTime = SDL_GetTicks();

void renderAll(Field *field, uint32_t state) {
    uint32_t beginTime = SDL_GetTicks();
    double delta = beginTime - endTime;
    if (delta > 1000/FPS) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, (!state
                                  ? STOP_TEXTURE
                                  : START_TEXTURE), NULL, &START_STOP_BUTTON);
        SDL_RenderCopy(renderer, CLEAR_TEXTURE, NULL, &CLEAR_BUTTON);
        SDL_SetRenderDrawColor(renderer, 0, 220, 0, 50);
        doForAll(field, drawElement);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderPresent(renderer);
        endTime = beginTime;
    }
}
