#pragma once

#include <stdint.h>

typedef struct Field Field;

typedef void (*elementHandler)(uint32_t i, uint32_t j);

uint32_t getWidth(Field* field);
uint32_t getHeight(Field* field);
uint32_t* fieldElm(Field* field, uint32_t i, uint32_t j);

Field* initField(uint32_t width, uint32_t size);

void doForAll(Field* field, elementHandler);
void deleteField(Field *f);
void copyField(Field *f1, Field *f2);
