#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Bakery.h>

Ingredient* create_ingredient(char* name, char* supplier, int quantity, int expiration_date_day,
                            int expiration_date_month, int expiration_date_year)
{
    Ingredient* i = malloc(sizeof(Ingredient));
    if(i == NULL)
        return NULL;
    i->name = malloc(sizeof(char) * ((strlen(name))+1));
    strcpy(i->name, name);

    i->supplier = malloc(sizeof(char) * ((strlen(supplier))+1));
    strcpy(i->supplier, supplier);
    i->quantity = quantity;
    i->expiration_date = malloc(sizeof(date));
    i->expiration_date->day = expiration_date_day;
    i->expiration_date->month = expiration_date_month;
    i->expiration_date->year = expiration_date_year;

    return i;
}
void destroy_ingredient(Ingredient* i)
{
    if(i == NULL)
        return;

    /// free the memory which was allocated for the component fields
    free(i->name);
    free(i->supplier);
    free(i->expiration_date);
    /// free the memory which was allocated for the planet structure
    free(i);
}

char* getName(Ingredient* i)
{
    if(i == NULL)
        return NULL;
    return i->name;
}
void setName(Ingredient* i, char const* name)
{
    free(i->name);

    i->name = malloc(sizeof(char) * ((strlen(name))+1));
    strcpy(i->name, name);
}

char* getSupplier(Ingredient* i)
{
    if(i == NULL)
        return NULL;
    return i->supplier;
}
void setSupplier(Ingredient* i, char const* supplier)
{
    free(i->supplier);

    i->supplier = malloc(sizeof(char) * ((strlen(supplier))+1));
    strcpy(i->supplier, supplier);
}

int getQuantity(Ingredient* i)
{
    if(i == NULL)
        return -1;

    return i->quantity;
}
void setQuantity(Ingredient* i, int quantity)
{
    i->quantity = quantity;
}

date* getExpirationDate(Ingredient* i)
{
    if(i == NULL)
        return NULL;
    return i->expiration_date;
}
void setExpirationDate(Ingredient* i, int day, int month, int year)
{
    if(day != 0)
        i->expiration_date->day = day;
    if(month != 0)
        i->expiration_date->month = month;
    if(year != 0)
        i->expiration_date->year = year;
}

void toString(Ingredient* i, char* str)
{
    if(i == NULL)
        return;
    sprintf(str, "Ingredient is %s from the supplier %s with the quantity %d and the expiration date"
                 " %d/%d/%d\n", i->name, i->supplier, i->quantity, i->expiration_date->day, i->expiration_date->month,
                 i->expiration_date->year);
}

Ingredient* copyIngredient(Ingredient* i)
{
    if(i == NULL)
        return NULL;
    return create_ingredient(i->name, i->supplier, i->quantity,
                             i->expiration_date->day, i->expiration_date->month,
                             i->expiration_date->year);
}