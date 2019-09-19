#include "field/field.h"
#include "utils/utils.h"
#include "mechanic/mechanic.h"
#include "renderer/renderer.h"
#include "constants.c"

const uint32_t WIN_WIDTH = 960, WIN_HEIGHT = 540;

int main()
{
    Field *field = initField(WIN_WIDTH, WIN_HEIGHT);
    initRenderer(field);
    state_t state;
    while(state = processEvents())
    {
        if (state == LIFE_STARTED)
        {
            processLife(field);
        }
        renderAll(field, state);
    }
    deleteRenderer();
}
