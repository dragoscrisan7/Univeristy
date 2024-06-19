#include "Parser.h"
#include "Grammar.h"

#pragma once

class Test {
private:
    bool passed;
    Parser parser;
    Grammar grammar;

public:
    Test();

    void initialize();

    void test_initialize();
    void test_expand();
    void test_advance();
    void test_momentaryInsuccess();
    void test_anotherTry();
    void test_back();
    void test_success();
    void test_parseExpression();
    void output();
};