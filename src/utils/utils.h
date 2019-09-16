#pragma once

#include "../constants.c"
#include "../field/field.h"

SDL_Texture* createTextTexture(SDL_Renderer *renderer, const char* message);
void init(void);
void processEvents(void);
void freeGameResorces(void);
