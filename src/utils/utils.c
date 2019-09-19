#include "utils.h"

#include <SDL2/SDL_ttf.h>
#include <assert.h>

#include "../constants.c"

SDL_Texture* createTextTexture(SDL_Renderer *renderer, const char* message) {
    TTF_Init();
    SDL_Color black = {0,0,0,0};
    TTF_Font *font = TTF_OpenFont("assets/lobster.ttf", 24);
    SDL_Surface* text = TTF_RenderUTF8_Blended(font,
                message, black);
    TTF_Quit();

    return SDL_CreateTextureFromSurface(renderer, text);
}

void mouseEventProcessing(Field *field, state_t *state) {
    int32_t mouseX, mouseY;
    SDL_GetMouseState(&mouseX,&mouseY);
    uint32_t* elm = fieldElm(field, (uint32_t)mouseX/CELL_SIDE, (uint32_t)mouseY/CELL_SIDE);
    if (mouseY < (int32_t)getHeight(field)) {
        if (mouseX < (int32_t)getWidth(field))
            *elm = (*elm ? 0 : 1);
    }
    else {
        if (mouseX > (int32_t)(getWidth(field) - BUTTON_WIDTH))
        {
            *state = (*state == LIFE_STARTED ? LIFE_STOPED : LIFE_STARTED);
        }
        else if (mouseX > 0 && mouseX < (int32_t)BUTTON_WIDTH)
        {
           field = initField(getWidth(field)/CELL_SIDE, getHeight(field)/CELL_SIDE);
        }
    }
}
state_t processEvents()
{
    state_t state = CONTINUE_GAME;
    static SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                state = mouseEventProcessing(*startLife);
                break;
            case SDL_QUIT:
                state = STOP_GAME;
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
    return state;
}
