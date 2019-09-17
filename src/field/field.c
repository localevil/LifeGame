#include "field.h"
#include <stdlib.h>

typedef struct Field
{
    uint32_t *fieldElements;
    uint32_t height, width;

}Field;

uint32_t getWidth(Field* field)
{
    return field->width;
}
uint32_t getHeight(Field* field)
{
    return field->height;
}
uint32_t* fieldElm(Field* field, uint32_t i, uint32_t j)
{
    return &field->fieldElements[i * field->height + j];
}

uint32_t fieldSize(Field *f)
{
    return f->width * f->height;
}

void doForAll(Field* field, elementHandler func)
{
    for (uint32_t i = 0; i < field->width; ++i) {
        for (uint32_t j = 0; j < field->height; ++j) {
            func(field, i ,j);
        }
    }
}

Field* initField(uint32_t width, uint32_t height)
{
    Field *f = {0};
    f->width = width;
    f->height = height;
    f->fieldElements = (uint32_t*)calloc(fieldSize(f), sizeof(uint32_t));
    return f;
}

void deleteField(Field *f) {
    free(f);
}

void copyField(Field *f1, Field *f2) {
    for (uint32_t i = 0; i < fieldSize(f2); ++i) {
        f1->fieldElements[i] = f2->fieldElements[i];
    }
}

