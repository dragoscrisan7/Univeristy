#ifndef A3_4_DRAGOSCRISAN7_BAKERY_REPOSITORY_H
#define A3_4_DRAGOSCRISAN7_BAKERY_REPOSITORY_H
#include <Dynamic_array.h>
#include <Bakery.h>

typedef struct
{
    Dynamic_array* array;
}IngredientRepo;

/// <summary>
/// Creates a IngredientRepo.
/// </summary>
///<returns> pointer to the IngredientRepo
IngredientRepo* createIngredientRepo();

/// <summary>
/// Destroys a given ingredient repository. The memory is freed.
/// </summary>
void destroyRepo(IngredientRepo* v);

/*
	Adds an ingredient to the repository of ingredients.
	Input:	- v - pointer to the IngredientRepo
			- i - ingredient
	Output: 1 - if the planet was successfully added
			0 - if the planet could not be added, as another planet with the same name already exists in the PlanetRepo.
*/
int add(IngredientRepo* v, Ingredient* i);
int delete_ing(IngredientRepo* v, char const* name, char const* supplier, int expiration_date_day,
               int expiration_date_month,int expiration_date_year);
int modify_ing(IngredientRepo* v, Ingredient* i, Ingredient* j);

int find(IngredientRepo* r, char const* name, char const* supplier, int expiration_date_day,
         int expiration_date_month,int expiration_date_year);

int get_Length(IngredientRepo* repo);
Dynamic_array* get_dyn_array(IngredientRepo* r);

Ingredient* getIngredientOnPos(IngredientRepo* r, int pos);

void test_Repo();

#endif //A3_4_DRAGOSCRISAN7_BAKERY_REPOSITORY_H
