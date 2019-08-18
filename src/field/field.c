#include "field.h"

unsigned int fieldSize(Field *f)
{
    return f->width * f->height;
}

Field* initField(unsigned int width,unsigned int height)
{
    Field *f = (Field*)malloc(sizeof (Field));
    f->width = width;
    f->height = height;
    f->fieldElements = (unsigned int**)malloc(width * sizeof(int*));
    for (unsigned int i = 0; i < width; i++) {
        f->fieldElements[i] = (unsigned int*)malloc(height * sizeof(int));
        for (unsigned int j = 0; j < height; ++j) {
            f->fieldElements[i][j] = 0;
        }
    }
    return f;
}

void drowField(Field *f, SDL_Renderer* ren) {
    SDL_SetRenderDrawColor(ren, 0, 220, 0, 50);
    unsigned int rectWall = 10;
    for (unsigned int i = 0; i < f->width; ++i) {
        for (unsigned int j = 0; j < f->height; ++j) {
            if (f->fieldElements[i][j] > 0) {
                SDL_Rect rect = {(int)(i * rectWall), (int)(j * rectWall), (int)(rectWall), (int)(rectWall)};
                SDL_RenderFillRect(ren, &rect);
            }
        }
    }
}


void deleteField(Field *f) {
    for (unsigned int i = 0; i < f->width; ++i) {
            free(f->fieldElements[i]);
        }
    free(f->fieldElements);
    free(f);
}

void copyField(Field *f1, Field *f2) {
    for (unsigned int i = 0; i < f2->width; ++i) {
        for (unsigned int j = 0; j < f2->height; ++j) {
            f1->fieldElements[i][j] = f2->fieldElements[i][j];
        }
    }
}

