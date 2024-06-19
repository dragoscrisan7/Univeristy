#include <iostream>
#include <cstring>
#include <cassert>
#include <vector>

template<typename T>
class Stack {
private:
    int maxCapacity;
    std::vector<T> elements;
public:
    class StackFullException: public std::exception {
    private:
        std::string message;
    public:
        StackFullException(const std::string &message) : message(message) {}

        const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
            return message.c_str();
        }
    };

    Stack<T> operator+(T t) {
        if (elements.size() == maxCapacity) {
//            throw std::exception();
            throw std::runtime_error("Stack is full!");
//            throw StackFullException("Stack is full!");
        }
        auto s = *this;
        s.elements.push_back(t);
        return s;
    }

    // no required implementation
    explicit Stack(int maxCapacity) : maxCapacity(maxCapacity) {}

    int getMaxCapacity() const {
        return maxCapacity;
    }

    T pop() {
        if (elements.empty()) {
            throw std::exception();
        }
        auto last = elements[elements.size() - 1];
        elements.pop_back();
        return last;
    }
};


void testStack() {
    Stack<std::string> s{2};
    assert(s.getMaxCapacity() == 2);
    try {
        s = s + "examination";
        s = s + "oop";
        s = s + "test";
    }
    catch (std::exception& e) {
        assert(strcmp(e.what(), "Stack is full!") == 0);
    }
    assert(s.pop() == "oop");
    assert(s.pop() == "examination");
}

int main() {
    testStack();
    return 0;
}
