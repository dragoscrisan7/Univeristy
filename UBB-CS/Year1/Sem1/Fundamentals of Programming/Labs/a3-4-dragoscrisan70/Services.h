#ifndef A3_4_DRAGOSCRISAN7_SERVICES_H
#define A3_4_DRAGOSCRISAN7_SERVICES_H
#include <Bakery_Repository.h>
#include <Bakery.h>
#include <Operation.h>

typedef struct
{
    IngredientRepo* repo;
    Dynamic_array* undoStack;
    Dynamic_array* redoStack;
}Service;

Service* createService(IngredientRepo* r);
void destroyService(Service* s);

/// <summary>
/// Adds an ingredient to the repository of ingredient.
/// </summary>
/// <param name="s">Pointer to the Service.</param>
/// <param name = "name">A string, the name of the ingredient.</param>
/// <param name = "supplier">A string, the ingredient's supplier.</param>
/// <param name = "quantity">Double, the ingredient's quantity.</param>
/// <param name = "expiration_date_day">A variable, the day of expiration.</param>
/// <param name = "expiration_date_month">A variable, the month of expiration.</param>
/// <param name = "expiration_date_year">A variable, the year of expiration.</param>
/// <returns>1 - if the planet was successfully added; 0 - if the planet could not be added, as another planet with
/// the same name already exists.</returns>
int addIngredient(Service* s, char* name, char* supplier, int quantity, int expiration_date_day,
                  int expiration_date_month, int expiration_date_year);

int removeIngredient(Service* s, char* name, char* supplier, int expiration_date_day,
                     int expiration_date_month, int expiration_date_year);
int modifyIngredient(Service* s, char* name, char* supplier, int expiration_date_day,
                     int expiration_date_month, int expiration_date_year, char* name2, char* supplier2, int quantity,
                     int expiration_date_day2, int expiration_date_month2, int expiration_date_year2);

IngredientRepo* getRepo(Service* s);

int undo(Service* s);
int redo(Service* s);

/// <summary>
/// Searches for the planets containing a given type.
/// </summary>
/// <param name="s">Pointer to the Service.</param>
/// <param name = "symbols">A string, the searched type; "null" - for all the planets.</param>
/// <returns>A pointer to a repository of planets, that have the given type.</returns>

Dynamic_array* past_expiration_date(Service* s, const char* str);
Dynamic_array* ingredients_from_supplier(Service* s, const char* str, int quantity);

void test_service();

#endif //A3_4_DRAGOSCRISAN7_SERVICES_H
