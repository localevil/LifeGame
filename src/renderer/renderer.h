#pragma once
#include "../field/field.h"

void initRenderer(Field* field);
void deleteRenderer();
void drawElement(Field* field, uint32_t i, uint32_t j);
void renderAll(uint32_t* endTime, uint32_t startLife);
