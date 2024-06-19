#ifndef A3_4_DRAGOSCRISAN7_DYNAMIC_ARRAY_H
#define A3_4_DRAGOSCRISAN7_DYNAMIC_ARRAY_H

typedef void* TElement;
typedef void (*DestroyElementFunctionType)(void*);

typedef struct
{
    TElement* elems;
    int capacity; ///capacity of the array
    int length; ///length of the array
    DestroyElementFunctionType destroyElemFct; /// function pointer to the function responsible for deallocating
    ///the elements stored in the array
}Dynamic_array;


/// <summary>
/// Creates a IngredientRepo.
/// </summary>
///<returns> pointer to the IngredientRepo
Dynamic_array* createDynamicArray(DestroyElementFunctionType destroyElemFct);

/// <summary>
/// Destroys a given ingredient repository. The memory is freed.
/// </summary>
void destroyDynamicArray(Dynamic_array* v);


/// <summary>
/// Finds the planet with the given name.
/// </summary>
/// <param name="v">Pointer to the IngredientRepo.</param>
/// <param name = "name">A string, the name to search for.</param>
/// <param name = "supplier">A string, the supplier to search for.</param>
/// <param name = "expiration_date_day">A variable, the day of expiration.</param>
/// <param name = "expiration_date_month">A variable, the month of expiration.</param>
/// <param name = "expiration_date_year">A variable, the year of expiration.</param>
/// <returns>pos - the position on which the planet with the given name is in the PlanetRepo; -1 -
/// if the planet does not exist.</returns>

/*
	Adds an ingredient to the repository of ingredients.
	Input:	- v - pointer to the IngredientRepo
			- i - ingredient
	Output: 1 - if the planet was successfully added
			0 - if the planet could not be added, as another planet with the same name already exists in the PlanetRepo.
*/
void add_dynamic(Dynamic_array* v, TElement* i);
void delete_dynamic(Dynamic_array* v, int pos);
int getLength(Dynamic_array* v);
///tests
TElement get(Dynamic_array* v, int pos);
void testDynamicArray();

#endif //A3_4_DRAGOSCRISAN7_DYNAMIC_ARRAY_H
