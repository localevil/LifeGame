#include <SDL2/SDL_ttf.h>
#include <assert.h>

#include "utils.h"

static bool startLife = 0;

typedef struct GameResorces
{
    Field* field;

    SDL_Renderer* renderer;
    SDL_Window* window;
}GameResorces;

static SDL_Texture* START_TEXTURE;
static SDL_Texture* STOP_TEXTURE;
static SDL_Texture* CLEAR_TEXTURE;

static GameResorces* gameResorces;

void freeGameResorces(void)
{
    deleteField(gameResorces->field);
    SDL_DestroyRenderer(gameResorces->renderer);
    SDL_DestroyWindow(gameResorces->window);
}

SDL_Texture* createTextTexture(SDL_Renderer *renderer, const char* message) {
    TTF_Init();
    SDL_Color black = {0,0,0,0};
    TTF_Font *font = TTF_OpenFont("assets/lobster.ttf", 24);
    SDL_Surface* text = TTF_RenderUTF8_Blended(font,
                message, black);
    TTF_Quit();

    return SDL_CreateTextureFromSurface(renderer, text);
}

void init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    gameResorces->window = SDL_CreateWindow("Window", 1,0, (int32_t)WIN_WIDTH, (int32_t)(WIN_HEIGHT + BUTTON_HEIGTH), SDL_WINDOW_SHOWN);
    assert(gameResorces->window != NULL);
    gameResorces->renderer = SDL_CreateRenderer(gameResorces->window, -1, SDL_RENDERER_ACCELERATED);
    assert(gameResorces->renderer != NULL);

    const char* START_TEXT = "Start";
    const char* STOP_TEXT = "Stop";
    const char* CLEAR_TEXT = "Clear";

    START_TEXTURE = createTextTexture(gameResorces->renderer, START_TEXT);
    STOP_TEXTURE  = createTextTexture(gameResorces->renderer, STOP_TEXT);
    CLEAR_TEXTURE = createTextTexture(gameResorces->renderer, CLEAR_TEXT);
    gameResorces->field = initField(WIN_WIDTH/CELL_SIDE, WIN_HEIGHT/CELL_SIDE);
}

void drawElement(uint32_t i, uint32_t j) {
    if (*fieldElm(gameResorces->field, i, j) > 0) {
        SDL_Rect rect = {(int32_t)(i * CELL_SIDE), (int32_t)(j * CELL_SIDE), (int32_t)(CELL_SIDE), (int32_t)(CELL_SIDE)};
        SDL_RenderFillRect(gameResorces->renderer, &rect);
    }
}

uint32_t renderAll(uint32_t endTime) {
    uint32_t beginTime = SDL_GetTicks();
    double delta = beginTime - endTime;
    if (delta > 1000/FPS) {
        SDL_RenderClear(gameResorces->renderer);
        SDL_RenderCopy(gameResorces->renderer, (startLife
                                  ? STOP_TEXTURE
                                  : START_TEXTURE), NULL, &START_STOP_BUTTON);
        SDL_RenderCopy(gameResorces->renderer, CLEAR_TEXTURE, NULL, &CLEAR_BUTTON);
        SDL_SetRenderDrawColor(gameResorces->renderer, 0, 220, 0, 50);
        doForAll(gameResorces->field, drawElement);
        SDL_SetRenderDrawColor(gameResorces->renderer, 255, 255, 255, 0);
        SDL_RenderPresent(gameResorces->renderer);
        if (startLife)
        {
            processLife(gameResorces->field);
        }
        endTime = beginTime;
    }
    return endTime;
}

void mouseEventProcessing(void) {
    int32_t mouseX, mouseY;
    SDL_GetMouseState(&mouseX,&mouseY);
    uint32_t* elm = fieldElm(gameResorces->field, (uint32_t)mouseX/CELL_SIDE, (uint32_t)mouseY/CELL_SIDE);
    if (mouseY < (int32_t)WIN_HEIGHT) {
        if (mouseX < (int32_t)WIN_WIDTH)
            *elm = (*elm ? 0 : 1);
    }
    else {
        if (mouseX > (int32_t)(WIN_WIDTH - BUTTON_WIDTH))
        {
            startLife = (startLife ? 0 : 1);
        }
        else if (mouseX > 0 && mouseX < (int32_t)BUTTON_WIDTH)
        {
           gameResorces->field = initField(WIN_WIDTH/CELL_SIDE, WIN_HEIGHT/CELL_SIDE);
        }
    }
}

void processEvents() {
    uint32_t endTime = SDL_GetTicks();
    SDL_Event event;
    bool isRuned = true;
    while(isRuned)
    {
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                mouseEventProcessing();
                break;
            case SDL_QUIT:
                isRuned = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                case SDLK_UP:
                    break;
                case SDLK_DOWN:
                    break;
                case SDLK_EJECT:
                    break;
                }
            }
        }
        endTime = renderAll(endTime);
    }
}
