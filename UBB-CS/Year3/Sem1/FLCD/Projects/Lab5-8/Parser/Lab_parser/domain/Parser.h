#pragma once
#include "Grammar.h"

class Parser {
private:
    Grammar grammar;
    char state;
    size_t inputPosition;
    std::string inputWord;
    std::string workingStack;
    std::string inputStack;
    std::string currentSymbol;

public: // this is temporary until I find a solution to not be public and be accessed by another class in the same package
    void expand(std::string nonTerminal);
    void advance();
    void momentaryInsuccess();
    void back();
    void anotherTry(std::string nonTerminal);
    void success();

public:
    Parser() {this->grammar = Grammar(); this->state = 'q'; this->inputPosition = 1; this->workingStack=""; this->inputStack=""; this->currentSymbol=' ';}
    Parser(Grammar grammar, const std::string& inputSequence);

    void parseExpression();
    void printOut(){std::cout << "State: " << this->state << " | Position: " << this->currentSymbol << " |  Working Stack: " << this->workingStack << " | Input Stack: " << this->inputStack << std::endl;}

    // Getters and setters
    Grammar getGrammar() {
        return grammar;
    }

    void setGrammar(Grammar grammar) {
        this->grammar = grammar;
    }

    char getState() {
        return state;
    }

    void setState(char state) {
        state = state;
    }

    size_t getInputPosition() {
        return inputPosition;
    }

    void setInputPosition(size_t inputPosition) {
        inputPosition = inputPosition;
    }

    std::string getWorkingStack() {
        return workingStack;
    }

    void setWorkingStack(std::string workingStack) {
        workingStack = workingStack;
    }

    std::string getInputStack() {
        return inputStack;
    }

    void setInputStack(std::string inputStack) {
        inputStack = inputStack;
    }

    std::string getCurrentSymbol() {
        return currentSymbol;
    }

    void setCurrentSymbol(char currentSymbol) {
        currentSymbol = currentSymbol;
    }
};
