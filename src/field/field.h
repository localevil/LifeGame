#ifndef FIELD
#define FIELD
static const unsigned int CELL_SIDE = 10;

typedef struct Field
{
    unsigned int **fieldElements;
    unsigned int height, width;

}Field;

Field* initField(unsigned int width, unsigned int size);

void doForAll(Field* field, void (*func)(unsigned int i, unsigned int j));
void deleteField(Field *f);
void copyField(Field *f1, Field *f2);
#endif
