#ifndef A3_4_DRAGOSCRISAN7_BAKERY_H
#define A3_4_DRAGOSCRISAN7_BAKERY_H

typedef struct
{
    int day;
    int month;
    int year;
}date;

typedef struct
{
    char* name;
    char* supplier;
    int quantity;
    date* expiration_date;

}Ingredient;

Ingredient* create_ingredient(char* name, char* supplier, int quantity, int expiration_date_day,
                            int expiration_date_month, int expiration_date_year);
void destroy_ingredient(Ingredient* i);

char* getName(Ingredient* i);
char* getSupplier(Ingredient* i);
int getQuantity(Ingredient* i);
date* getExpirationDate(Ingredient* i);

void setName(Ingredient* i,char const* name);
void setSupplier(Ingredient* i, char const* supplier);
void setQuantity(Ingredient* i, int quantity);
void setExpirationDate(Ingredient* i, int day, int month, int year);

Ingredient* copyIngredient(Ingredient* i);

void toString(Ingredient* i, char* str);

void test_Domain();

#endif //A3_4_DRAGOSCRISAN7_BAKERY_H
