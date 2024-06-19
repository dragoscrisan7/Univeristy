#include <iostream>
#include "domain/SymbolTable.h"
#include "domain/Scanner.h"
#include "domain/FA.h"
#include "domain/Grammar.h"
#include <fstream>

using namespace std;

int main() {

    FA fa = FA();
    fa.read_file();
    fa.is_deterministic();
    fa.display();

    SymbolTable st;
    Scanner s;
    s.tokenize();

    Grammar gr;

    return 0;
}