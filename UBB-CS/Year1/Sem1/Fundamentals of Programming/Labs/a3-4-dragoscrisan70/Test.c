#import "Test.h"
#import <assert.h>
#import <string.h>

void test_Domain()
{
    Ingredient* i2 = NULL;
    assert(getName(i2) == NULL);
    assert(getSupplier(i2) == NULL);
    assert(getQuantity(i2) == -1);
    assert(getExpirationDate(i2) == NULL);
    destroy_ingredient(i2);

    Ingredient* ing = create_ingredient("ala", "bala", 20, 3,
                                        3, 2022);
    assert(!strcmp(getName(ing),"ala"));
    assert(!strcmp(getSupplier(ing),"bala"));
    assert(getQuantity(ing) == 20);
    date* date2 = getExpirationDate(ing);
    assert(date2->day == 3);
    assert(date2->month == 3);
    assert(date2->year == 2022);

    setName(ing,"brr");
    setSupplier(ing,"grr");
    setQuantity(ing, 10);
    setExpirationDate(ing, 5,0,2023);

    assert(!strcmp(getName(ing),"brr"));
    assert(!strcmp(getSupplier(ing),"grr"));
    assert(getQuantity(ing) == 10);
    date2 = getExpirationDate(ing);
    assert(date2->day == 5);
    assert(date2->month == 3);
    assert(date2->year == 2023);

    char str[200];
    toString(ing, str);
    assert(!strcmp(str,"Ingredient is brr from the supplier grr with the quantity 10 and the expiration date 5/3/2023\n"));

    Ingredient* i3 = copyIngredient(ing);
    assert(!strcmp(getName(i3),"brr"));
    assert(!strcmp(getSupplier(i3),"grr"));
    assert(getQuantity(i3) == 10);
    date2 = getExpirationDate(i3);
    assert(date2->day == 5);
    assert(date2->month == 3);
    assert(date2->year == 2023);

    destroy_ingredient(ing);
    destroy_ingredient(i3);
}

void test_Repo()
{
    IngredientRepo* repo = createIngredientRepo();
    assert(get_Length(repo) == 5);

    Ingredient* ing = getIngredientOnPos(repo, 1);
    assert(!strcmp(getName(ing),"yoghurt"));
    assert(!strcmp(getSupplier(ing),"Napolact"));
    assert(getQuantity(ing) == 5);
    date* date2 = getExpirationDate(ing);
    assert(date2->day == 5);
    assert(date2->month == 5);
    assert(date2->year == 2023);


    delete_ing(repo, getName(ing), getSupplier(ing), date2->day,
               date2->month, date2->year);
    assert(get_Length(repo) == 4);

    ing = getIngredientOnPos(repo, 0);
    Ingredient* i = create_ingredient("a", "a", 10, 3, 3,
                                      2023);
    modify_ing(repo, ing, i);
    destroy_ingredient(ing);

    ing = getIngredientOnPos(repo, 0);
    assert(!strcmp(getName(ing),"a"));
    assert(!strcmp(getSupplier(ing),"a"));
    assert(getQuantity(ing) == 10);
    date2 = getExpirationDate(ing);
    assert(date2->day == 3);
    assert(date2->month == 3);
    assert(date2->year == 2023);

    destroyRepo(repo);
}

void test_service()
{
    IngredientRepo* r = createIngredientRepo();
    Service* s = createService(r);

    addIngredient(s,"iaurt", "Napolact", 5, 5, 10, 2023);
    IngredientRepo* repo = getRepo(s);
    assert(get_Length(repo) == 6);

    Ingredient* i = getIngredientOnPos(repo, 5);
    assert(!strcmp(getName(i),"iaurt"));
    assert(!strcmp(getSupplier(i),"Napolact"));
    assert(getQuantity(i) == 5);
    date* eDate = getExpirationDate(i);
    assert(eDate->day == 5);
    assert(eDate->month == 10);
    assert(eDate->year == 2023);

    assert(getLength(s->undoStack) == 1);
    Operation* op = get(s->undoStack, 0);
    assert(getOpType(op) == ADD);
    Ingredient* j = getOpObject(op);
    assert(!strcmp(getName(j),"iaurt"));

    removeIngredient(s, "iaurt", "Napolact", 5, 10, 2023);
    assert(getLength(s->undoStack) == 2);
    op = get(s->undoStack, 1);
    assert(getOpType(op) == DELETE);

    assert(undo(s) == 1);
    assert(getLength(s->undoStack) == 1);
    assert(get_Length(s->repo) == 6);
    assert(undo(s) == 1);
    assert(get_Length(s->repo) == 5);
    assert(undo(s) == 0);

    assert(getLength(s->redoStack) == 2);
    assert(redo(s) == 1);
    assert(get_Length(s->repo) == 6);
    assert(redo(s) == 1);
    assert(get_Length(s->repo) == 5);
    assert(redo(s) == 0);

    assert(undo(s) == 1);
    assert(getLength(s->undoStack) == 1);
    assert(get_Length(s->repo) == 6);
    assert(undo(s) == 1);
    assert(get_Length(s->repo) == 5);
    assert(undo(s) == 0);

    j = getIngredientOnPos(s->repo, 1);
    eDate = getExpirationDate(j);
    modifyIngredient(s, getName(j), getSupplier(j), eDate->day, eDate->month,
                     eDate->year, "a", "a", 10, 3, 3,
                     2023);
    i = getIngredientOnPos(s->repo, 1);
    assert(!strcmp(getName(i),"a"));
    assert(!strcmp(getSupplier(i),"a"));
    assert(getQuantity(i) == 10);
    eDate = getExpirationDate(i);
    assert(eDate->day == 3);
    assert(eDate->month == 3);
    assert(eDate->year == 2023);

    assert(undo(s) == 1);
    Ingredient* ing = getIngredientOnPos(s->repo, 1);
    assert(!strcmp(getName(ing),"yoghurt"));
    assert(!strcmp(getSupplier(ing),"Napolact"));
    assert(getQuantity(ing) == 5);
    date* date2 = getExpirationDate(ing);
    assert(date2->day == 5);
    assert(date2->month == 5);
    assert(date2->year == 2023);

    assert(redo(s) == 1);
    i = getIngredientOnPos(s->repo, 1);
    assert(!strcmp(getName(i),"a"));
    assert(!strcmp(getSupplier(i),"a"));
    assert(getQuantity(i) == 10);
    eDate = getExpirationDate(i);
    assert(eDate->day == 3);
    assert(eDate->month == 3);
    assert(eDate->year == 2023);



    destroyService(s);
}

void run_tests()
{
    test_Domain();
    test_Repo();
    test_service();
}
