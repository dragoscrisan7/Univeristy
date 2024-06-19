#include <stack>
#include "Parser.h"

Parser::Parser(Grammar grammar, const std::string& inputWord)
        : grammar(grammar), state('q'), inputPosition(1), inputWord(inputWord){}


void Parser::expand(std::string nonTerminal) {
    const auto& productionsMap = grammar.getProductions();
    auto it = productionsMap.find(nonTerminal);///get production options

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
            workingStack += "1";///push nonTerminal and production number to stack
            currentSymbol = inputStack[0];
        }
    }
}

void Parser::advance() {
    if (!inputStack.empty()) {
        ///currentSymbol = inputStack.front();


        inputStack.erase(inputStack.begin());///advance the input position

        workingStack += currentSymbol;///push to stack
        currentSymbol = inputStack[0];
        ++inputPosition;
    }
}

void Parser::momentaryInsuccess() {
    state = 'b';///switch to back stat
    currentSymbol = grammar.getStartingSymbol();
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

void Parser::anotherTry(std::string nonTerminal) {
    const auto& productionsMap = grammar.getProductions();
    auto it = productionsMap.find(nonTerminal);

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
            currentSymbol = inputStack[0];
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
    if (inputPosition - 1 == inputWord.size() && inputStack.empty()) {///maybe add check for inputStack = inputWord?
        state = 'f';///go to final state
    }
}

void Parser::parseExpression() {
    state = 'q'; ///initial state
    inputPosition = 1; ///initial input position
    workingStack = ""; ///empty working stack
    currentSymbol = grammar.getStartingSymbol();

    while (state != 'f' && state != 'e') {
        if (state == 'q') {
            if (inputPosition - 1 == inputWord.size() && inputStack.empty()) {
                success();
            }else {
                if (inputPosition - 1 == inputWord.size() && !inputStack.empty()) {
                    state = 'e';
                } else {
                    if (currentSymbol == inputWord.substr(inputPosition - 1, currentSymbol.size())) {
                        advance();
                        //printOut();
                    } else if (isupper(currentSymbol[0])) {
                        expand(currentSymbol);
                        //printOut();
                    } else {
                        momentaryInsuccess();
                        //printOut();
                    }
                }
            }
        } else if (state == 'b') {
            if (isalnum(workingStack.back())) {
                std::string lastTerminal = workingStack.substr(workingStack.size() - 1);
                if (lastTerminal == currentSymbol) {
                    back();
                    //printOut();
                } else {
                    anotherTry(currentSymbol);
                    //printOut();
                }
            } else {
                momentaryInsuccess();
                //printOut();
            }
        }
    }

    if (state == 'e') {
        std::cout << "Error\n";
    } else {
        std::cout << "Sequence accepted\n";
    }

    // You may want to include logic for BuildStringOfProd(a) based on your specific requirements.
}