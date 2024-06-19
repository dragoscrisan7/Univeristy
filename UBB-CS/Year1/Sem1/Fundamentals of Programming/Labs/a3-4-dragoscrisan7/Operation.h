#ifndef A3_4_DRAGOSCRISAN7_OPERATION_H
#define A3_4_DRAGOSCRISAN7_OPERATION_H
#include <Bakery.h>

typedef enum{
    ADD,
    DELETE,
    MODIFY
}opType;

typedef struct{
    opType type;
    Ingredient* i;
    Ingredient* j;
}Operation;

Operation* createOperation(opType, Ingredient* i, Ingredient* j);
void destroyOperation(Operation* o);

opType getOpType(Operation* o);
Ingredient* getOpObject(Operation* o);
Ingredient* getOpObject2(Operation* o);

#endif //A3_4_DRAGOSCRISAN7_OPERATION_H
