#include "renderer.h"

#include <assert.h>
#include <SDL2/SDL.h>
#include "../constants.c"

static SDL_Renderer* renderer;

void initRenderer(SDL_Window* window)
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    assert(renderer != NULL);
}

void deleteRenderer()
{
    SDL_DestroyRenderer(renderer);
    assert(renderer == NULL);
}

void drawElement(Field* field, uint32_t i, uint32_t j) {
    if (*fieldElm(field, i, j) > 0) {
        SDL_Rect rect = {(int32_t)(i * CELL_SIDE), (int32_t)(j * CELL_SIDE), (int32_t)(CELL_SIDE), (int32_t)(CELL_SIDE)};
        SDL_RenderFillRect(renderer, &rect);
    }
}

void renderAll(uint32_t* endTime, bool startLife) {
    uint32_t beginTime = SDL_GetTicks();
    double delta = beginTime - *endTime;
    if (delta > 1000/FPS) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, (startLife
                                  ? STOP_TEXTURE
                                  : START_TEXTURE), NULL, &START_STOP_BUTTON);
        SDL_RenderCopy(renderer, CLEAR_TEXTURE, NULL, &CLEAR_BUTTON);
        SDL_SetRenderDrawColor(renderer, 0, 220, 0, 50);
        doForAll(field, drawElement);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderPresent(renderer);
        *endTime = beginTime;
    }
}
