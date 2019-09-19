#pragma once
#include "../field/field.h"

enum {
    STOP_GAME,
    CONTINUE_GAME,
    LIFE_STARTED,
    LIFE_STOPED
} state_t;

void init(Field *field);
state_t processEvents(Field *field);
