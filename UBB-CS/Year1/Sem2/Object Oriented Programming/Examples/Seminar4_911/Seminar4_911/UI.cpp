#include "UI.h"

void UI::print_menu() {
	std::cout << "\n1. Print analyses\n";
	std::cout << "2. Show all analyses between 2 dates\n";
	std::cout << "3. Exit\n\n";
}

UI::UI(Person& p) : person(p) {}

void UI::start() {
	while (true) {
		print_menu();
		int opt;

		std::cout << "option>";
		std::cin >> opt;

		switch (opt) {
		case 1: {
			auto v = this->person.getAllAnalyses();
			for (auto it : v) {
				std::cout << it->toString() << '\n';
			}
			break;
		}
		case 2:

			break;
		case 3:
			return;
		default:
			std::cout << "Invalid option!\n";
			break;
		}
	}
}
