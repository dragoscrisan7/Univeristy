#include <UI.h>
#include <stdio.h>
#include <stdlib.h>

Ui* createUI(Service* s)
{
    Ui* ui = malloc(sizeof(Ui));
    if(ui == NULL)
        return NULL;
    ui->serv = s;

    return ui;
}

void destroyUI(Ui* ui)
{
    if(ui == NULL)
        return;
    destroyService(ui->serv);
    free(ui);
}

/*
	Reads an integer number from the keyboard. Asks for number while read errors encoutered.
	Input: the message to be displayed when asking the user for input.
	Returns the number.
*/
int readIntegerNumber(const char* message)
{
    char s[16] = { 0 };
    int res = 0;
    int flag = 0;

    while (flag == 0)
    {
        printf("%s", message);
        scanf("%15s", s);

        int r = sscanf(s, "%d", &res);	// reads data from s and stores them as integer, if possible; returns 1 if successful
        flag = (r == 1);
        if (flag == 0)
            printf("Error reading number!\n");
    }
    return res;
}

int add_Ingredient(Ui* ui)
{
    char name[50], supplier[50];
    int quantity, expiration_date_day, expiration_date_month, expiration_date_year;
    printf("Please input name: ");
    scanf("%49s", name);
    printf("Please input supplier: ");
    scanf("%49s", supplier);
    quantity = readIntegerNumber("Please input quantity: ");
    expiration_date_day = readIntegerNumber("Please input expiration date day: ");
    expiration_date_month = readIntegerNumber("Please input expiration date month: ");
    expiration_date_year = readIntegerNumber("Please input expiration date year: ");

    return addIngredient(ui->serv, name, supplier, quantity, expiration_date_day, expiration_date_month,
                         expiration_date_year);
}
int delete_ingredient(Ui* ui)
{
    char name[50], supplier[50];
    int  expiration_date_day, expiration_date_month, expiration_date_year;
    printf("Please input name: ");
    scanf("%49s", name);
    printf("Please input supplier: ");
    scanf("%49s", supplier);
    expiration_date_day = readIntegerNumber("Please input expiration date day: ");
    expiration_date_month = readIntegerNumber("Please input expiration date month: ");
    expiration_date_year = readIntegerNumber("Please input expiration date year: ");

    return removeIngredient(ui->serv, name, supplier, expiration_date_day, expiration_date_month,
                            expiration_date_year);
}

int modify_ingredient(Ui* ui)
{
    char name[50], name2[50], supplier[50], supplier2[50];
    int expiration_date_day, expiration_date_month, expiration_date_year, expiration_date_day2, expiration_date_month2;
    int expiration_date_year2, quantity;
    printf("Please input name: ");
    scanf("%49s", name);
    printf("Please input supplier: ");
    scanf("%49s", supplier);
    expiration_date_day = readIntegerNumber("Please input expiration date day: ");
    expiration_date_month = readIntegerNumber("Please input expiration date month: ");
    expiration_date_year = readIntegerNumber("Please input expiration date year: ");

    printf("Please input the modified ingredient: \n");
    printf("Please input name: ");
    scanf("%49s", name2);
    printf("Please input supplier: ");
    scanf("%49s", supplier2);
    quantity = readIntegerNumber("Please input quantity: ");
    expiration_date_day2 = readIntegerNumber("Please input expiration date day: ");
    expiration_date_month2 = readIntegerNumber("Please input expiration date month: ");
    expiration_date_year2 = readIntegerNumber("Please input expiration date year: ");

    return modifyIngredient(ui->serv, name, supplier, expiration_date_day, expiration_date_month, expiration_date_year,
                      name2, supplier2, quantity, expiration_date_day2, expiration_date_month2, expiration_date_year2);
}

void past_e_date(Ui* ui)
{
    char string[100];
    printf("Enter string to search by: ");

    scanf("%s", string);

    Dynamic_array* dyn = past_expiration_date(ui->serv, string);
    for(int i=0; i<dyn->length; i++)
    {
        toString(dyn->elems[i], string);
        printf("%s", string);
    }
    free(dyn);
}
void sorted_quantity(Ui* ui)
{
    char string[100];
    printf("Enter supplier: ");

    scanf("%s", string);
    int x = readIntegerNumber("Input minimum quantity: ");

    Dynamic_array* dyn = ingredients_from_supplier(ui->serv, string, x);
    if(dyn == NULL)
        printf("No ingredients match your search criteria\n");
    else
    {
        for(int i=0; i<dyn->length; i++)
        {
            toString(dyn->elems[i], string);
            printf("%s", string);
        }
    }
    free(dyn);
}

void print_array(Ui* ui)
{
    char str[150];
    IngredientRepo* repo = getRepo(ui->serv);
    Ingredient* ing;
    for(int i=0; i< get_Length(repo); i++)
    {
        ing = getIngredientOnPos(repo, i);
        toString(ing, str);
        printf("%s", str);
    }
}
int Undo(Ui* ui)
{
    return undo(ui->serv);
}
int Redo(Ui* ui)
{
    return redo(ui->serv);
}

void print_menu()
{
    printf("**********************************************************\n");
    printf("Type 1 to add a new ingredient\nType 2 to delete an ingredient\n"
             "Type 3 to modify an ingredient\nType 4 to print all ingredients\nType 5 to print"
             " all ingredients containing a string past their expiration date\nType 6 to print"
             " all elements with less quantity than selected from the given supplier\nType 7 to undo last operation\n"
             "Type 8 to redo last undo'd operation\nType 0 to exit\n");
    printf("**********************************************************\n");
}

void run(Ui* ui)
{
    while (1)
    {
        print_menu();
        int option = readIntegerNumber("Option: ");
        if(option == 0)
            break;
        switch(option) {
            case 1: {
                int val = add_Ingredient(ui);
                if(val == 0)
                    printf("Ingredient already exists, quantity modified successfully\n");
                else if(val == 1)
                    printf("Ingredient added successfully\n");
                else
                    printf("Error, corrupted repository or dynamic array");
                break;
            }
            case 2: {
                int val = delete_ingredient(ui);
                if(val == 0)
                    printf("Ingredient could not be found\n");
                else if(val == 1)
                    printf("Ingredient successfully deleted\n");
                else
                    printf("Error, corrupted repository or dynamic array");
                break;
            }
            case 3: {
                int val = modify_ingredient(ui);
                if(val == 0)
                    printf("Ingredient could not be found\n");
                else if(val == 1)
                    printf("Ingredient successfully updated\n");
                else
                    printf("Error, corrupted repository or dynamic array");
                break;
            }
            case 4: {
                print_array(ui);

                break;
            }
            case 5: {
                past_e_date(ui);

                break;
            }
            case 6: {
                sorted_quantity(ui);

                break;
            }
            case 7: {
                int val = Undo(ui);
                if(val == 0)
                    printf("No more operations to undo\n");
                else if(val == 1)
                    printf("Operation successfully undo'd\n");
                else
                    printf("Error, corrupted repository or dynamic array");

                break;
            }
            case 8 :{
                int val = Redo(ui);
                if(val == 0)
                    printf("No more operations to redo\n");
                else if(val == 1)
                    printf("Operation successfully redo'd\n");
                else
                    printf("Error, corrupted repository or dynamic array");

                break;
            }
            default:
                printf("Wrong input\n");
                break;
        }
    }
}