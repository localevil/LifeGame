#include "renderer.h"

#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../constants.h"

static SDL_Window* window;
static SDL_Renderer* renderer;

static SDL_Texture* START_TEXTURE;
static SDL_Texture* STOP_TEXTURE;
static SDL_Texture* CLEAR_TEXTURE;

const double FPS = 30.0;

static uint32_t endTime;

static SDL_Rect START_STOP_BUTTON;
static SDL_Rect CLEAR_BUTTON;

SDL_Texture* createTextTexture(SDL_Renderer *renderer, const char* message, TTF_Font *font) {
    SDL_Color black = {0,0,0,0};
    SDL_Surface* text = TTF_RenderUTF8_Blended(font,
                message, black);
    SDL_Texture* result = SDL_CreateTextureFromSurface(renderer, text);
    SDL_FreeSurface(text);
    return result;
}

void initRenderer()
{

    SDL_Rect tmp_start_stop = {(int32_t)(WIN_WIDTH - BUTTON_WIDTH), (int32_t)WIN_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGTH};
    START_STOP_BUTTON = tmp_start_stop;

    SDL_Rect tmp_clear = {0, (int32_t)WIN_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGTH};
    CLEAR_BUTTON = tmp_clear;

    SDL_Init(SDL_INIT_EVERYTHING);
    
    window = SDL_CreateWindow("Window", 1,0, (int32_t)WIN_WIDTH, (int32_t)(WIN_HEIGHT + BUTTON_HEIGTH), SDL_WINDOW_SHOWN);
    assert(window != NULL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    assert(renderer != NULL);
    
    const char* START_TEXT = "Start";
    const char* STOP_TEXT = "Stop";
    const char* CLEAR_TEXT = "Clear";

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("assets/lobster.ttf", 24);
    START_TEXTURE = createTextTexture(renderer, START_TEXT, font);
    STOP_TEXTURE  = createTextTexture(renderer, STOP_TEXT, font);
    CLEAR_TEXTURE = createTextTexture(renderer, CLEAR_TEXT, font);
    TTF_CloseFont(font);
    TTF_Quit();

    endTime = SDL_GetTicks();
}

void deleteRenderer()
{
    SDL_DestroyTexture(START_TEXTURE);
    SDL_DestroyTexture(STOP_TEXTURE);
    SDL_DestroyTexture(CLEAR_TEXTURE);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);    
}

void drawElement(Field* field, uint32_t i, uint32_t j) {
    if (*fieldElm(field, i, j) > 0) {
        SDL_Rect rect = {(int32_t)(i * CELL_SIDE), (int32_t)(j * CELL_SIDE), (int32_t)(CELL_SIDE), (int32_t)(CELL_SIDE)};
        SDL_RenderFillRect(renderer, &rect);
    }
}

void renderAll(Field *field, bool startLife)
{
    while (true) {
        uint32_t beginTime = SDL_GetTicks();
        double delta = beginTime - endTime;
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
            endTime = beginTime;
            break;
        }
    }
}
