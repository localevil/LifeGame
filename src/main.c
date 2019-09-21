#include "field/field.h"
#include "mechanic/mechanic.h"
#include "renderer/renderer.h"
#include "utils/utils.h"

int main()
{
    Field *field = field =initField(WIN_WIDTH/CELL_SIDE,WIN_HEIGHT/CELL_SIDE);
    initRenderer();
    state_t state = CONTINUE_GAME;
    for(;state;processEvents(field, &state))
    {
        bool startLife = state == LIFE_PROCESSED;
        if (startLife)
        {
            processLife(field);
        }
        renderAll(field, startLife);
    }
    deleteRenderer();
    deleteField(field);
}
