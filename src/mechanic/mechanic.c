#include "mechanic.h"

int processLife(Field *f) {
    Field *newField = initField(f->width, f->height);
    for (unsigned int i = 0; i < f->width; ++i) {
        for (unsigned int j = 0; j < f->height; ++j) {
            int lifeCount = checkLife(f, i, j);
            if (f->fieldElements[i][j] == 1
                       && lifeCount > 2 && lifeCount < 5) {
                newField->fieldElements[i][j] = 1;
            } else if (lifeCount == 3)
            {
                newField->fieldElements[i][j] = 1;
            }
        }
    }
    copyField(f, newField);
    deleteField(newField);
    return 0;
}

int checkLife(Field *f,unsigned int x,unsigned int y) {
    int lifeCounter = 0;
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            int firstInd = (int)x + i;
            int secondInd = (int)y + j;
            if (firstInd >= 0 && secondInd >= 0
                    && firstInd < (int)f->width && secondInd < (int)f->height
                    && f->fieldElements[firstInd][secondInd] > 0)
                lifeCounter++;
        }
    }
    return lifeCounter;
}
