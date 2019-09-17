#include <SDL2/SDL_ttf.h>
#include <assert.h>

#include "utils.h"

typedef struct GameResorces
{
    Field* field;
    
    SDL_Window* window;
}GameResorces;

static SDL_Texture* START_TEXTURE;
static SDL_Texture* STOP_TEXTURE;
static SDL_Texture* CLEAR_TEXTURE;

static GameResorces* gameResorces;

void freeGameResorces(void)
{
    deleteField(gameResorces->field);
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

    const char* START_TEXT = "Start";
    const char* STOP_TEXT = "Stop";
    const char* CLEAR_TEXT = "Clear";

    START_TEXTURE = createTextTexture(gameResorces->renderer, START_TEXT);
    STOP_TEXTURE  = createTextTexture(gameResorces->renderer, STOP_TEXT);
    CLEAR_TEXTURE = createTextTexture(gameResorces->renderer, CLEAR_TEXT);
    gameResorces->field = initField(WIN_WIDTH/CELL_SIDE, WIN_HEIGHT/CELL_SIDE);
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
