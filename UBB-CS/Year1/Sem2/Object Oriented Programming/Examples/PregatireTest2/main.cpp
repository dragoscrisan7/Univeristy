#include <iostream>
#include "UserInterface.h"

int main() {
    UserInterface ui;
    ui.start();
    std::cout << "Goodbye, World!" << std::endl;
    return 0;
}
