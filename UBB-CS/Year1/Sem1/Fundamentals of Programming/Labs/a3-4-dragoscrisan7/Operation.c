#include <Operation.h>
#include <Bakery.h>
#include <stdlib.h>

Operation* createOperation(opType type, Ingredient* ing1, Ingredient* ing2)
{
    Operation* op = malloc(sizeof(Operation));
    op->type = type;

    Ingredient* ing = copyIngredient(ing1);
    op->i = ing;
    ing = copyIngredient(ing2);
    op->j = ing;

    return op;
}

void destroyOperation(Operation* o)
{
    if(o == NULL)
        return;

    destroy_ingredient(o->j);
    destroy_ingredient(o->i);
    free(o);
}

opType getOpType(Operation* o)
{
    if(o == NULL)
        return -1;

    return o->type;
}

Ingredient* getOpObject(Operation* o)
{
    if(o == NULL)
        return NULL;

    return o->i;
}
Ingredient* getOpObject2(Operation* o)
{
    if(o == NULL)
        return NULL;

    return o->j;
}