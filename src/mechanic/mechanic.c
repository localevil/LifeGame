#include "mechanic.h"

void processLife(Field *f) {
    Field *newField = initField(getWidth(f), getWidth(f));
    for (uint32_t i = 0; i < getWidth(f); ++i) {
        for (uint32_t j = 0; j < getHeight(f); ++j) {
            uint32_t lifeCount = checkLife(f, i, j);
            if (*fieldElm(f,i, j) == 1
                       && lifeCount > 2 && lifeCount < 5) {
                *fieldElm(newField, i, j) = 1;
            } else if (lifeCount == 3)
            {
                *fieldElm(newField, i, j) = 1;
            }
        }
    }
    copyField(f, newField);
    deleteField(newField);
    return;
}

uint32_t checkLife(Field *f, uint32_t x, uint32_t y) {
    uint32_t lifeCounter = 0;
    for (int32_t i = -1; i < 2; ++i) {
        for (int32_t j = -1; j < 2; ++j) {
            int32_t firstInd = (int32_t)x + i;
            int32_t secondInd = (int32_t)y + j;
            if (firstInd >= 0 && secondInd >= 0
                    && firstInd < (int32_t)getWidth(f) && secondInd < (int32_t)getHeight(f)
                    && *fieldElm(f,(uint32_t)firstInd, (uint32_t)secondInd) > 0)
                lifeCounter++;
        }
    }
    return lifeCounter;
}
