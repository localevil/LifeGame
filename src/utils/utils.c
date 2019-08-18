#include "utils.h"

#include <SDL2/SDL_ttf.h>

SDL_Texture* createTextTexture(SDL_Renderer *renderer, const char* message) {
    TTF_Init();
    SDL_Color black = {0,0,0,0};
    TTF_Font *font = TTF_OpenFont("assets/lobster.ttf", 24);
    SDL_Surface* text = TTF_RenderUTF8_Blended(font,
                message, black);
    TTF_Quit();

    return SDL_CreateTextureFromSurface(renderer, text);
}
