#include <iostream>
#include <cassert>
#include <cstring>
#include <vector>

using namespace std;

class Complex {
private:
    int real;
    int imaginary;
public:
    Complex(int real, int imaginary) : real(real), imaginary(imaginary) {}
//    Complex() = default; // also works
    Complex() : Complex(0, 0) {};
    Complex(const Complex& o): Complex(o.real, o.imaginary) {}
    int getReal() const { return real; }
    int getImaginary() const { return imaginary; }
    bool operator==(const Complex& o) const { return real == o.real && imaginary == o.imaginary; }
    Complex operator/(int x) const {
        if (not x)
            throw std::runtime_error("Division by zero!");
        return {real / x, imaginary / x};
    }
    friend std::ostream &operator<<(std::ostream &os, const Complex &c) {
        os << c.real << "+" << c.imaginary << "i";
        return os;
    }
};

template<typename T>
class Vector {
private:
    std::vector<T> v;
public:
    Vector(std::vector<T> v) : v(v) {}

    void printAll(std::ostream &os) const {
        for (const auto &e: v) {
            os << e << ", ";
        }
    }
};

void complex() {
    Complex a{}, b{1, 2}, c{6, 4}, d{b};
    assert(a.getReal() == 0 && a.getImaginary() == 0);
    assert(b == d);
    Complex res1 = c / 2;
    cout << res1 << "\n"; // prints: 3+2i
    try {
        Complex res2 = b / 0;
    }
    catch (runtime_error& e) {
        assert(strcmp(e.what(), "Division by zero!") == 0);
    }

    Vector<string> v1{std::vector<string>{"hello", "bye"}};
    v1.printAll(std::cout); // prints: hello, bye,

    Vector<Complex> v2{std::vector<Complex>{a, b, c, d}};
    v2.printAll(std::cout); // prints: 0+0i, 1+2i, 6+4i, 1+2i,
}

int main() {
    complex();
    return 0;
}
