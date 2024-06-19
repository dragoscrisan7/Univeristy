#include "Parser.h"

Parser::Parser(Grammar grammar, const std::string& inputWord)
        : grammar(grammar), state('q'), inputPosition(1), inputWord(inputWord){}


void Parser::expand(char nonTerminal) {
    const auto& productionsMap = grammar.getProductions();
    auto it = productionsMap.find(std::string(1, nonTerminal));///get production options

    if (it != grammar.getProductions().end()) {
        const std::vector<std::string>& productionOptions = it->second;

        if (!productionOptions.empty()) {
            if (!inputStack.empty() && isupper(inputStack[0])) {///push the actual production to stack
                inputStack = productionOptions[0] + inputStack.substr(1);
            } else {
                inputStack += productionOptions[0];
            }

            const std::string& selectedProduction = productionOptions[0];///choose the first one
            workingStack += nonTerminal;
            workingStack += '1';///push nonTerminal and production number to stack
            currentSymbol = inputStack[0];
        }
    }
}

void Parser::advance() {
    if (!inputStack.empty()) {
        char currentSymbol = inputStack.front();

        inputStack.erase(inputStack.begin());///advance the input position

        workingStack += currentSymbol;///push to stack
        currentSymbol = inputStack[0];
        ++inputPosition;
    }
}

void Parser::momentaryInsuccess() {
    state = 'b';///switch to back state
}

void Parser::back() {
    if (!workingStack.empty()) {
        if(isalnum(workingStack.back())) {
            workingStack.pop_back();///remove the last terminal from the working stack
        }
        workingStack.pop_back();
        --inputPosition;///move back one position in the input sequence
        state = 'b';///go to back state
    }
}

void Parser::anotherTry(char nonTerminal) {
    const auto& productionsMap = grammar.getProductions();
    auto it = productionsMap.find(std::string(1, nonTerminal));

    if (it != grammar.getProductions().end()) {
        const std::vector<std::string>& productionOptions = it->second;

        if (!productionOptions.empty()) {
            char charDigit = workingStack.back();
            int production_number = charDigit - '1';
            production_number++;
            workingStack.pop_back();
            charDigit++;
            int productionLength = productionOptions[production_number-1].length();
            workingStack += charDigit;///push to stack
            inputStack = productionOptions[production_number] + inputStack.substr(productionLength);
            state = 'q';///go to normal state
        } else {
            if (inputPosition == 1 && nonTerminal == grammar.getStartingSymbol()) {
                state = 'e';///error state if i = 1 and A = S
            } else {
                state = 'b';///keep back state
            }
        }
    }
}

void Parser::success() {
    if (inputPosition == inputStack.size() && workingStack.empty()) {///maybe add check for inputStack = inputWord?
        state = 'f';///go to final state
    }
}

void Parser::parseExpression() {
    state = 'q'; ///initial state
    inputPosition = 1;///initial input position
    workingStack = "";///empty working stack
    currentSymbol = grammar.getStartingSymbol();

    expand(currentSymbol);
    advance();
    momentaryInsuccess();
    back();
    anotherTry(currentSymbol);
    success();

    // Print the current state and working stack after each function call
    std::cout << "State: " << state << ", Working Stack: " << workingStack << std::endl;



    // Start parsing with the initial configuration
//    while (state != 'f' && state != 'e') {
//        switch (state) {
//            case 'q':
//                if (isupper(currentSymbol)) {
//                    expand(currentSymbol);
//                } else {
//                    momentaryInsuccess();
//                }
//                break;
//
//            case 'b':
//                if (isupper(currentSymbol)) {
//                    back();
//                } else {
//                    anotherTry(currentSymbol);
//                }
//                break;
//        }
//    }
//
//    if (state == 'e') {
//        std::cout << "Error: Sequence not accepted\n";
//    } else {
//        std::cout << "Sequence accepted\n";
//    }
}