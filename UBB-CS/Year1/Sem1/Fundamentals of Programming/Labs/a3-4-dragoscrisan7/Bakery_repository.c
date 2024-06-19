#include <Bakery_Repository.h>
#include <stdlib.h>
#include <string.h>

void dynamic_array_default_values(IngredientRepo* v)
{
    Ingredient* i = create_ingredient("flour", "Baneasa", 3, 4,
                                      12, 2023);
    add(v,i);
    i = create_ingredient("yoghurt", "Napolact", 5, 5,
                          5, 2023);
    add(v,i);
    i = create_ingredient("rice", "Baneasa",6,6,
                          3,2025);
    add(v,i);
    i = create_ingredient("salt", "Pepper",7,20,
                          7,2030);
    add(v,i);
    i = create_ingredient("sugar", "Pepper",10,25,
                          11,2025);
    add(v,i);
}
IngredientRepo* createIngredientRepo()
{
    IngredientRepo* repo = (IngredientRepo*)malloc(sizeof(IngredientRepo));
    if(repo == NULL)
        return NULL;
    repo->array = createDynamicArray((DestroyElementFunctionType) &destroy_ingredient);
    dynamic_array_default_values(repo);

    return repo;
}
void destroyRepo(IngredientRepo* v)
{
    if(v == NULL)
        return;
    destroyDynamicArray(v->array);
    free(v);
}

int find(IngredientRepo* r, char const* name, char const* supplier, int expiration_date_day,
         int expiration_date_month,int expiration_date_year)
{
    for(int i=0; i< get_Length(r); i++)
    {
        Ingredient* ing = get(r->array, i);
        date* eDate = getExpirationDate(ing);
        if(!strcmp(getName(ing), name) && !strcmp(getSupplier(ing), supplier) &&
           eDate->day == expiration_date_day && eDate->month == expiration_date_month && eDate->year == expiration_date_year)
            return i;
    }

    return -1;
}

int add(IngredientRepo* v, Ingredient* i)
{
    if (v == NULL || i == NULL)
        return -1;

    add_dynamic(v->array, (TElement) i);

    return 1;
}
int delete_ing(IngredientRepo* r, char const* name, char const* supplier, int expiration_date_day,
               int expiration_date_month,int expiration_date_year)
{
    if(r == NULL)
        return -1;

    int x = find(r, name, supplier, expiration_date_day, expiration_date_month, expiration_date_year);
    if(x == -1)
        return 0;

    delete_dynamic(r->array, x);
    return 1;
}
int modify_ing(IngredientRepo* r, Ingredient* i, Ingredient* j)
{
    if(r == NULL)
        return -1;

    date* date2 = getExpirationDate(i);
    int x = find(r, getName(i), getSupplier(i), date2->day,
                 date2->month, date2->year);
    if(x == -1)
        return 0;

    Dynamic_array* da = r->array;
    da->elems[x] = j;
    return 1;
}

int get_Length(IngredientRepo* repo)
{
    if(repo->array == NULL)
        return -1;
    return getLength(repo->array);
}
Ingredient* getIngredientOnPos(IngredientRepo* r, int pos)
{
    if(r == NULL)
        return NULL;
    return get(r->array, pos);
}
Dynamic_array* get_dyn_array(IngredientRepo* repo)
{
    return repo->array;
}