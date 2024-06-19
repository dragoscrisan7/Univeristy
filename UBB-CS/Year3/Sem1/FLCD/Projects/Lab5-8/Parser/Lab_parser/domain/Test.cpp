#include "Test.h"
#include <cassert>

Test::Test() {}

void Test::initialize() {
    this->grammar.read_grammar_from_file();
    this->parser = Parser(this->grammar, "aacbc");
    this->passed = true;
    std::cout << "------------ TESTS STARTED -----------\n";
}

void Test::test_initialize() {
    try {
        Parser p;

        assert(p.getState() == 'q');
        assert(p.getWorkingStack() == "");
        assert(p.getInputStack() == "");
        assert(p.getInputPosition() == 1);

        std::cout << "------------ TEST PASSED: PARSER INITIALIZE -----------\n";

    } catch (std::exception e) {
        this->passed = false;
        std::cout << "INITIALIZE TEST: Something went wrong.\n";
    }
}

void Test::test_expand() {
    try {
        Parser p(this->grammar, "aacbc");
        p.expand("S");

        assert(p.getState() == 'q');
        assert(p.getInputPosition() == 1);
        assert(p.getWorkingStack() == "S1");
        assert(p.getInputStack() == "aSbS");

        std::cout << "------------ TEST PASSED: EXPAND -----------\n";

    } catch (std::exception e) {
        this->passed = false;
        std::cout << "EXPAND TEST: Something went wrong.\n";
    }
}

void Test::test_advance() {
    try {
        Parser p(this->grammar, "aacbc");
        p.expand("S");
        p.advance();

        assert(p.getState() == 'q');
        assert(p.getInputPosition() == 2);
        assert(p.getWorkingStack() == "S1a");
        assert(p.getInputStack() == "SbS");

        std::cout << "------------ TEST PASSED: ADVANCE -----------\n";

    } catch (std::exception e) {
        this->passed = false;
        std::cout << "ADVANCE TEST: Something went wrong.\n";
    }
}

void Test::test_momentaryInsuccess() {
    try {
        Parser p(this->grammar, "aacbc");
        p.expand("S");
        p.advance();
        p.expand("S");
        p.advance();
        p.expand("S");
        p.momentaryInsuccess();

        assert(p.getState() == 'b');
        assert(p.getInputPosition() == 3);
        assert(p.getWorkingStack() == "S1aS1aS1");
        assert(p.getInputStack() == "aSbSbSbS");

        std::cout << "------------ TEST PASSED: MOMENTARY INSUCCESS -----------\n";

    } catch (std::exception e) {
        this->passed = false;
        std::cout << "MOMENTARY INSUCCESS TEST: Something went wrong.\n";
    }
}

void Test::test_back() {
    try {
        Grammar g = Grammar();
        std::string name = R"(C:\Users\Dragos\Facultate_no-Onedrive\UniveristyGithub\UBB-CS\Year3\Semester 1\LFTC\Projects\Lab5-8\Parser\Lab_parser\grammar_files\test_back_grammar.txt)";
        g.setFileName(name);
        g.read_grammar_from_file();
        Parser p = Parser(g, "aaa");
        p.expand("S");
        p.advance();
        p.expand("S");
        p.advance();
        p.expand("S");
        p.advance();
        p.expand("S");
        p.momentaryInsuccess();
        p.back();

        assert(p.getState() == 'b');
        assert(p.getInputPosition() == 3);
        assert(p.getWorkingStack() == "S1aS1aS1a");
        assert(p.getInputStack() == "aS");

        std::cout << "------------ TEST PASSED: BACK -----------\n";

    } catch (std::exception e) {
        this->passed = false;
        std::cout << "BACK TEST: Something went wrong.\n";
    }
}

void Test::test_anotherTry() {
    try {
        Parser p(this->grammar, "aacbc");
        p.expand("S");
        p.advance();
        p.expand("S");
        p.advance();
        p.expand("S");
        p.momentaryInsuccess();
        p.anotherTry("S");

        assert(p.getState() == 'q');
        assert(p.getInputPosition() == 3);
        assert(p.getWorkingStack() == "S1aS1aS2");
        assert(p.getInputStack() == "aSbSbS");

        std::cout << "------------ TEST PASSED: ANOTHER TRY -----------\n";

    } catch (std::exception e) {
        this->passed = false;
        std::cout << "ANOTHER TRY TEST: Something went wrong.\n";
    }
}

void Test::test_success() {
    try {
        Parser p(this->grammar, "aacbcbc");
        p.parseExpression();

        assert(p.getState() == 'f');
        assert(p.getInputPosition() == 8);
        assert(p.getWorkingStack() == "S1aS1aS3cbS3cbS3c");
        assert(p.getInputStack() == "");

        std::cout << "------------ TEST PASSED: SUCCESS -----------\n";

    } catch (std::exception e) {
        this->passed = false;
        std::cout << "SUCCESS TEST: Something went wrong.\n";
    }
}

void Test::test_parseExpression() {
    try {
        Parser p(this->grammar, "aacbc");
        p.parseExpression();

        assert(p.getState() == 'e');
        assert(p.getInputPosition() == 6);
        assert(p.getWorkingStack() == "S1aS1aS3cbS3c");
        assert(p.getInputStack() == "bS");

        std::cout << "------------ TEST PASSED: PARSING -----------\n";

    } catch (std::exception e) {
        this->passed = false;
        std::cout << "PARSEEXPRESSION TEST: Something went wrong.\n";
    }
}

void Test::output() {
    if (passed == false)
        std::cout << "------------ VERDICT: TESTS NOT PASSED -----------\n";
    else
        std::cout << "------------ VERDICT: TESTS PASSED -----------\n";
}
