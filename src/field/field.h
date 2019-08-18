#ifndef FIELD
#define FIELD

#include <SDL2/SDL.h>

typedef struct Field
{
    unsigned int **fieldElements;
    unsigned int height;
    unsigned int width;
}Field;

Field* initField(unsigned int width, unsigned int size);

void drowField(Field *f, SDL_Renderer* ren);
void deleteField(Field *f);
void copyField(Field *f1, Field *f2);
#endif
