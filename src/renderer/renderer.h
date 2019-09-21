#pragma once
#include "../field/field.h"
#include "stdbool.h"

void initRenderer(void);
void deleteRenderer(void);
void drawElement(Field* field, uint32_t i, uint32_t j);
void renderAll(Field* field, bool startLife);
