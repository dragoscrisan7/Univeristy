#include <Dynamic_array.h>
#include <stdlib.h>

Dynamic_array* createDynamicArray(DestroyElementFunctionType destroyElemFct)
{
    Dynamic_array* v = malloc(sizeof(Dynamic_array));
    ///make sure that the space was allocated
    if(v == NULL)
        return NULL;
    v->length = 0;
    v->capacity = 2;
    ///make space for the elements
    v->elems = (TElement*)malloc(v->capacity * sizeof(TElement));
    v->destroyElemFct = destroyElemFct;

    return v;
}
void destroyDynamicArray(Dynamic_array* v)
{
    if(v == NULL)
        return;
    for(int i=0; i<v->length; i++)
        v->destroyElemFct(v->elems[i]);
    free(v->elems);
    v->elems = NULL;
    free(v);
    v = NULL;
}
void reallocDynamicArray(Dynamic_array* v)
{
    v->capacity = v->capacity * v->capacity;
    TElement* aux = (TElement*) malloc(v->capacity*sizeof(TElement));
    for(int i=0; i <v->length; i++)
        aux[i] = v->elems[i];
    free(v->elems);
    v->elems = aux;

}

void add_dynamic(Dynamic_array* v, TElement* i)
{
    if(v->length >= v->capacity)
        reallocDynamicArray(v);
    v->elems[v->length++] = i;
}
void delete_dynamic(Dynamic_array* v, int pos)
{
    if(v == NULL || pos < 0 || pos >= v->length)
        return;

    v->destroyElemFct(v->elems[pos]);

    if(pos != v->length - 1)
        v->elems[pos] = v->elems[v->length - 1];
    v->length--;
}

int getLength(Dynamic_array* v)
{
    if(v == NULL)
        return -1;

    return v->length;
}
TElement get(Dynamic_array* v, int pos)
{
    if(v == NULL)
        return NULL;
    if(pos < 0 || pos >= v->length)
        return NULL;
    return v->elems[pos];
}