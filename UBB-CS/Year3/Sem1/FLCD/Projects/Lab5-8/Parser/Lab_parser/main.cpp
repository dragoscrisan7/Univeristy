#include <iostream>
#include "domain/Test.h"
#include "domain/FA.h"
#include "domain/SymbolTable.h"
#include "domain/Scanner.h"

int main() {
//    FA fa = FA();
//    fa.read_file();
//    fa.is_deterministic();
//    fa.display();
//
//    SymbolTable st;
//    Scanner s;
//    s.tokenize();

    Grammar g2;
    g2.setFileName("..\\grammar_files\\g2.txt");
    g2.read_grammar_from_file2();
//    g2.print_nonterminals();
//    g2.print_terminals();
//    std::cout<<"Starting point: "<<g2.get_starting() << std::endl;
//    std::cout<<"Production symbol: "<<g2.get_prod() << std::endl;
//    g2.print_productions();
//
//    std::cout<<g2.is_cfg()<<std::endl;
//
//    std::string letter2;



    Grammar g;
    ///g.setFileName("..\\grammar_files\\g2.txt");
    g.read_grammar_from_file();

    g.print_nonterminals();
    g.print_terminals();
    std::cout<<"Starting point: "<<g.get_starting() << std::endl;
    std::cout<<"Production symbol: "<<g.get_prod() << std::endl;
    g.print_productions();

    std::cout<<g.is_cfg()<<std::endl;

    std::string letter;
    // This part is for reading a non-terminal and seeing their productions

//    bool validNonTerminal = false;
//
//    while (!validNonTerminal) {
//        std::cout << "Give a nonterminal: ";
//        std::cin >> letter;
//
//        try {
//            g.productions_for_nonterminal(letter);
//            validNonTerminal = true;
//        } catch (std::invalid_argument e) {
//            std::cerr << "Error: " << e.what() << ". That's not a letter." << std::endl;
//        }
//    }

    std::string inputSequence = "aacbcbc";
    ///std::string inputSequence = "aacbcbc";
    Parser p = Parser(g, inputSequence);

    // Tests
    try {
        Test t = Test();
        t.initialize();
        t.test_initialize();
        t.test_expand();
        t.test_advance();
        t.test_momentaryInsuccess();
        t.test_anotherTry();
        t.test_back();
        t.test_parseExpression();
        t.test_success();
        t.output();
    }
    catch(std::exception e){
        std::cerr << "TESTS DID NOT PASS from various reasons" <<std::endl;
    }

    // Parsing
    p.parseExpression();


    //TODO g2.txt + PIF.out
    return 0;
}
