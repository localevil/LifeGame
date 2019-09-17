#include "utils/utils.h"

int main()
{
    bool startLife = false;
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
                    mouseEventProcessing(*startLife);
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
        if (startLife)
        {
            processLife(field);
        }
        renderAll(endTime, startLife);
    }
}
