#pragma once
#include "Person.h"

class UI {
private:
	Person person;

	void print_menu();
public:
	UI(Person& p);
	void start();
};