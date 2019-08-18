#include <assert.h>

#include "utils/utils.h"
#include "mechanic/mechanic.h"

static const unsigned int WIN_WIDTH = 960, WIN_HEIGHT = 540;

static const double FPS = 5.0;

static const unsigned int BUTTON_WIDTH = 100, BUTTON_HEIGTH = 50;

static unsigned int isRuned = 1;
static unsigned int startLife = 0;

static const SDL_Rect START_STOP_BUTTON = {WIN_WIDTH - BUTTON_WIDTH, WIN_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGTH};
static const SDL_Rect CLEAR_BUTTON = {0, WIN_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGTH};

static SDL_Renderer* renderer = NULL;
static SDL_Window* win = NULL;
static Field* field = NULL;

static const SDL_Texture* START_TEXTURE = NULL;
static const SDL_Texture* STOP_TEXTURE = NULL;
static const SDL_Texture* CLEAR_TEXTURE = NULL;

void initSDL(int widWidth, int winHeight) {
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow("Window", 1,0, widWidth, winHeight + (int)BUTTON_HEIGTH, SDL_WINDOW_SHOWN);
    assert(win != NULL);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    assert(renderer != NULL);

    const char* START_TEXT = "Start";
    const char* STOP_TEXT = "Stop";
    const char* CLEAR_TEXT = "Clear";

    START_TEXTURE = createTextTexture(renderer, START_TEXT);
    STOP_TEXTURE  = createTextTexture(renderer, STOP_TEXT);
    CLEAR_TEXTURE = createTextTexture(renderer, CLEAR_TEXT);
    field = initField(WIN_WIDTH/CELL_SIDE, WIN_HEIGHT/CELL_SIDE);
}

void drowElement(unsigned int i, unsigned int j) {
    if (field->fieldElements[i][j] > 0) {
        SDL_Rect rect = {(int)(i * CELL_SIDE), (int)(j * CELL_SIDE), (int)(CELL_SIDE), (int)(CELL_SIDE)};
        SDL_RenderFillRect(renderer, &rect);
    }
}

unsigned int renderAll(unsigned int endTime) {
    unsigned int beginTime = SDL_GetTicks();
    double delta = beginTime - endTime;
    if (delta > 1000/FPS) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, (startLife
                                  ? STOP_TEXTURE
                                  : START_TEXTURE), NULL, &START_STOP_BUTTON);
        SDL_RenderCopy(renderer, CLEAR_TEXTURE, NULL, &CLEAR_BUTTON);
        SDL_SetRenderDrawColor(renderer, 0, 220, 0, 50);
        doForAll(field, drowElement);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderPresent(renderer);
        if (startLife)
        {
            processLife(field);
        }
        endTime = beginTime;
    }
    return endTime;
}

void mouseEventProcessing() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX,&mouseY);
    unsigned int* elm = &field->fieldElements[mouseX/(int)CELL_SIDE][mouseY/(int)CELL_SIDE];
    if (mouseY < (int)WIN_HEIGHT) {
        if (mouseX < (int)WIN_WIDTH)
            *elm = (*elm ? 0 : 1);
    }
    else {
        if (mouseX > (int)(WIN_WIDTH - BUTTON_WIDTH))
        {
            startLife = (startLife ? 0 : 1);
        }
        else if (mouseX > 0 && mouseX < (int)BUTTON_WIDTH)
        {
           field = initField(WIN_WIDTH/CELL_SIDE, WIN_HEIGHT/CELL_SIDE);
        }
    }
}

void processEvents() {
    unsigned int endTime = SDL_GetTicks();
    SDL_Event event;
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

int main()
{
    initSDL(WIN_WIDTH, WIN_HEIGHT);

    processEvents();

    deleteField(field);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    return 0;
}
