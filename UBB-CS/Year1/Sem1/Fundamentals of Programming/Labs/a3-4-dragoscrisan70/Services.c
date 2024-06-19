#include "Services.h"
#include <stdlib.h>
#include <string.h>

Service* createService(IngredientRepo* r)
{
    Service* s = (Service*)malloc(sizeof(Service));
    if(s == NULL)
        return NULL;
    s->repo = r;
    s->undoStack = createDynamicArray((DestroyElementFunctionType) &destroyOperation);
    s->redoStack = createDynamicArray((DestroyElementFunctionType) &destroyOperation);

    return s;
}

void destroyService(Service* s)
{
    destroyRepo(s->repo);
    destroyDynamicArray(s->undoStack);
    destroyDynamicArray(s->redoStack);

    free(s);
}

int addIngredient(Service* s, char* name, char* supplier, int quantity, int expiration_date_day,
                  int expiration_date_month, int expiration_date_year)
{
    int res;
    int x = find(s->repo,name, supplier, expiration_date_day, expiration_date_month, expiration_date_year);
    if(x == -1) {
        Ingredient *i = create_ingredient(name, supplier, quantity, expiration_date_day, expiration_date_month,
                                          expiration_date_year);
        res = add(s->repo, i);
        if (res == 1)///the ingredient was added
        {
            Operation *op = createOperation(ADD, i, NULL);
            if (op == NULL) {
                return -1;

            }
            add_dynamic(s->undoStack, (TElement) op);
        }
    }
    else
    {
        Ingredient* i = getIngredientOnPos(s->repo, x);
        quantity = quantity + getQuantity(i);
        Ingredient *j = create_ingredient(name, supplier, quantity, expiration_date_day, expiration_date_month,
                                          expiration_date_year);

        Operation* op = createOperation(MODIFY, j, i);
        modify_ing(s->repo, i ,j);
        add_dynamic(s->undoStack, (TElement) op);

        res = 0;
    }

    return res;
}
int removeIngredient(Service* s,char* name, char* supplier, int expiration_date_day,
                     int expiration_date_month, int expiration_date_year)
{
    int x = find(s->repo, name, supplier, expiration_date_day, expiration_date_month, expiration_date_year);
    Ingredient* i = getIngredientOnPos(s->repo, x);
    Operation* op = createOperation(DELETE, i, NULL);
    if(op == NULL)
        return -1;
    add_dynamic(s->undoStack, (TElement) op);

    return delete_ing(s->repo, name, supplier, expiration_date_day, expiration_date_month, expiration_date_year);
}
int modifyIngredient(Service* s, char* name, char* supplier, int expiration_date_day,
                     int expiration_date_month, int expiration_date_year, char* name2, char* supplier2, int quantity,
                     int expiration_date_day2, int expiration_date_month2, int expiration_date_year2) {
    int pos = find(s->repo, name, supplier, expiration_date_day, expiration_date_month, expiration_date_year);
    Ingredient* i = getIngredientOnPos(s->repo, pos);
    Ingredient* j = create_ingredient(name2, supplier2, quantity, expiration_date_day2,
                                      expiration_date_month2, expiration_date_year2);

    Operation* op = createOperation(MODIFY, j, i);
    add_dynamic(s->undoStack, (TElement) op);

    int x = modify_ing(s->repo, i, j);
    destroy_ingredient(i);
    return x;
}
int modifyIngredientWithoutUndo(Service* s, char* name, char* supplier, int expiration_date_day,
                                int expiration_date_month, int expiration_date_year, char* name2, char* supplier2, int quantity,
                                int expiration_date_day2, int expiration_date_month2, int expiration_date_year2) {
    int pos = find(s->repo, name, supplier, expiration_date_day, expiration_date_month, expiration_date_year);
    Ingredient* i = getIngredientOnPos(s->repo, pos);
    Ingredient* j = create_ingredient(name2, supplier2, quantity, expiration_date_day2,
                                      expiration_date_month2, expiration_date_year2);

    int x = modify_ing(s->repo, i, j);
    destroy_ingredient(i);
    return x;
}
int undo(Service* s)
{
    if(s == NULL)
        return -1;

    int stackSize = getLength(s->undoStack);
    if(stackSize == 0)
        return 0;
    Operation* op = get(s->undoStack, stackSize -1);
    if(op == NULL)
        return -1;
    Ingredient* i = getOpObject(op);
    if(i == NULL)
        return -1;
    Operation* op2 = NULL;

    if(getOpType(op) == ADD)
    {
        op2 = createOperation(ADD, i, NULL);
        date* date2 = getExpirationDate(i);
        delete_ing(s->repo, getName(i), getSupplier(i), date2->day,
                   date2->month, date2->year);
    }
    else if(getOpType(op) == DELETE)
    {
        op2 = createOperation(DELETE, i, NULL);
        add(s->repo, copyIngredient(i));
    }
    else if(getOpType(op) == MODIFY)
    {
        Ingredient* j = getOpObject2(op);
        if(j == NULL)
            return -1;
        op2 = createOperation(MODIFY, j, i);
        date* date2 = getExpirationDate(i);
        date* date3 = getExpirationDate(j);
        modifyIngredientWithoutUndo(s, getName(i), getSupplier(i), date2->day,
                         date2->month, date2->year, getName(j),
                         getSupplier(j), getQuantity(j) ,date3->day,
                         date3->month, date3->year);
    }

    add_dynamic(s->redoStack, (TElement) op2);
    delete_dynamic(s->undoStack, stackSize-1);
    return 1;
}
int redo(Service* s)
{
    if(s == NULL)
        return -1;

    int stackSize = getLength(s->redoStack);
    if(stackSize == 0)
        return 0;
    Operation* op = get(s->redoStack, stackSize -1);
    if(op == NULL)
        return -1;
    Ingredient* i = getOpObject(op);
    if(i == NULL)
        return -1;
    Operation* op2 = NULL;

    if(getOpType(op) == ADD)
    {
        op2 = createOperation(ADD, i, NULL);
        add(s->repo, copyIngredient(i));
    }
    else if(getOpType(op) == DELETE)
    {
        op2 = createOperation(DELETE, i, NULL);
        date* date2 = getExpirationDate(i);
        delete_ing(s->repo, getName(i), getSupplier(i), date2->day,
                   date2->month, date2->year);
    }
    else if(getOpType(op) == MODIFY)
    {
        Ingredient* j = getOpObject2(op);
        if(j == NULL)
            return -1;
        op2 = createOperation(MODIFY, j, i);
        date* date2 = getExpirationDate(i);
        date* date3 = getExpirationDate(j);
        modifyIngredientWithoutUndo(s, getName(i), getSupplier(i), date2->day,
                         date2->month, date2->year, getName(j),
                         getSupplier(j), getQuantity(j) ,date3->day,
                         date3->month, date3->year);
    }

    add_dynamic(s->undoStack, (TElement) op2);
    delete_dynamic(s->redoStack, stackSize-1);
    return 1;
}


Dynamic_array* past_expiration_date(Service* s, const char* str)
{
    Dynamic_array* da = createDynamicArray((DestroyElementFunctionType) destroy_ingredient);
    Dynamic_array* dyn = get_dyn_array(s->repo);
    for(int i=0; i< getLength(dyn); i++)
    {
        if(str[0] == '*' || strstr(getName(dyn->elems[i]), str) != NULL) {
            date *PEDate = getExpirationDate(dyn->elems[i]);
            if (PEDate->year > 2022)
                add_dynamic(da, dyn->elems[i]);
            else if (PEDate->year == 2022) {
                if (PEDate->month > 3 || (PEDate->month == 3 && PEDate->day >= 16))
                    add_dynamic(da, dyn->elems[i]);
            }
        }
    }
    return da;
}
Dynamic_array* ingredients_from_supplier(Service* s, const char* str, int quantity)
{
    Dynamic_array* dyn = get_dyn_array(s->repo);
    Dynamic_array* da = createDynamicArray((DestroyElementFunctionType) destroy_ingredient);
    for(int i=0; i< getLength(dyn); i++)
    {
        if(!strcmp(getSupplier(dyn->elems[i]),str) && getQuantity(dyn->elems[i]) <= quantity)
            add_dynamic(da, dyn->elems[i]);
    }
    if(getLength(da) == 0)
        return NULL;
    Ingredient* k;
    for(int i=0; i< getLength(da)-1; i++)
    {
        for(int j=i+1; j< getLength(da);j++)
        {
            if(getQuantity(da->elems[i]) > getQuantity(da->elems[j]))
            {
                k = da->elems[i];
                da->elems[i] = da->elems[j];
                da->elems[j] = k;
            }
        }
    }
    return da;
}

IngredientRepo* getRepo(Service* s)
{
    return s->repo;
}