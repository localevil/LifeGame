#pragma once

#include <stdint.h>

#include "../field/field.h"

void processLife(Field *f);
uint32_t checkLife(Field *f, uint32_t x, uint32_t y);
