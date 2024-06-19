#include <iostream>


class E {
public:
    E() { std::cout << "E{}"; }
    virtual ~E() { std::cout << "~E()"; }
};


class DE: public E {
public:
    static int n;
    DE() { n++; }
};

int DE::n = 0;


int fct2(int x) {
    if (x < 0) {
        throw E{};
        std::cout << "number less than 0" << std::endl;
    } else if (x == 0) {
        throw DE{};
        std::cout << "number equal to 0" << std::endl;
    }
    return x % 10;
}

// prints: E{}0~E()
// detailed description:
//  fct2(-5) and, since -5 < 0, E is thrown, and E's constructor is called,
//  printing "E{}".
//  E is caught in main, then DE::n is printed, which is 0.
// the execution reaches the end of the catch statement and the destructor of E is called,
// printing ~E()
int main() {
    try {
        int res = 0;
        res = fct2(-5);
        std::cout << DE::n;
        res = fct2(0);
        std::cout << DE::n;
        res = fct2(25);
        std::cout << DE::n;

    }
    catch (E&) {
        std::cout << DE::n;
    }

    return 0;
}
