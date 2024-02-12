#include "Item.h"

Item::Item() {
    category = "";
    name = "";
    quantity = 0;
}

Item::Item(string c, string n, int q) {
    category = c;
    name = n;
    quantity = q;
}

string Item::To_string() {
    string str = "Category: " + category + ", Name: " + name + ", Quantity: " + to_string(quantity) + "\n";
    return str;
}

