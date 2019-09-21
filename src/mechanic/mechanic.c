#include "mechanic.h"

#include <SDL2/SDL.h>
#include <assert.h>
#include <stdbool.h>

void processLife(Field *f) {
    Field *newField = initField(getWidth(f), getHeight(f));
    for (uint32_t i = 0; i < getWidth(f); ++i) {
        for (uint32_t j = 0; j < getHeight(f); ++j) {
            uint32_t lifeCount = checkLife(f, i, j);
            if (*fieldElm(f,i, j) == 1
                       && lifeCount > 2 && lifeCount < 5) {
                *fieldElm(newField, i, j) = 1;
            } else if (lifeCount == 3)
            {
                *fieldElm(newField, i, j) = 1;
            }
        }
    }
    copyField(f, newField);
    deleteField(newField);
    return;
}

uint32_t checkLife(Field *f, uint32_t x, uint32_t y) {
    uint32_t lifeCounter = 0;
    for (int32_t i = -1; i < 2; ++i) {
        for (int32_t j = -1; j < 2; ++j) {
            int32_t firstInd = (int32_t)x + i;
            int32_t secondInd = (int32_t)y + j;
            if (firstInd >= 0 && secondInd >= 0
                    && firstInd < (int32_t)getWidth(f) && secondInd < (int32_t)getHeight(f)
                    && *fieldElm(f,(uint32_t)firstInd, (uint32_t)secondInd) > 0)
                lifeCounter++;
        }
    }
    return lifeCounter;
}

void mouseEventProcessing(Field *field, state_t *state) {
    int32_t mouseX, mouseY;
    SDL_GetMouseState(&mouseX,&mouseY);
    uint32_t* elm = fieldElm(field, (uint32_t)mouseX/CELL_SIDE, (uint32_t)mouseY/CELL_SIDE);
    if (mouseY < (int32_t)WIN_HEIGHT) {
        if (mouseX < (int32_t)WIN_WIDTH)
            *elm = (*elm ? 0 : 1);
    }
    else {
        if (mouseX > (int32_t)(WIN_WIDTH- BUTTON_WIDTH))
        {
            *state = (*state == LIFE_PROCESSED ? CONTINUE_GAME : LIFE_PROCESSED);
        }
        else if (mouseX > 0 && mouseX < (int32_t)BUTTON_WIDTH)
        {
           clearField(field);
        }
    }
}


void processEvents(Field* field, state_t* state)
{
    static SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                mouseEventProcessing(field, state);
                break;
            case SDL_QUIT:
                *state = STOP_GAME;
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
}
