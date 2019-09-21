#pragma once
#include "../field/field.h"
#include "../constants.h"

void processLife(Field *f);
uint32_t checkLife(Field *f, uint32_t x, uint32_t y);
void processEvents(Field *field, state_t * state);
