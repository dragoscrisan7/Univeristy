#include <iostream>

using namespace std;

class Vector {
    int* elems;
    int size;
public:
    Vector(): size{0} { elems = new int[10]; }
    void add(int elem) { elems[size++] = elem; }
    int& operator[](int pos) {
        if (pos < 0 || pos >= size)
            throw std::runtime_error("Index out of bounds.");
        return elems[pos];
    }
    ~Vector() { delete[] elems; }

/*    Vector(const Vector& v): size{v.size}, elems{new int[v.size]} {
        std::copy(v.elems, v.elems + size, elems);
    }*/
};

// w/o copy constructor it would print: "2 1 2 1 " (the point is that the 1st value on the 2nd line is changed too, since the 2 Vector instance contains a pointer to the same heap location)
// w/ copy constructor it would print: "2 1 0 1"
// uncomment the copy constructor to see the change

// NOTE: I put "\n" in cout statements for flushing the stdout buffer (so I can see with the debugger)
//  switch between w/ and w/o newlines:  - replace between |<< "\n"| and |/*<< "\n*/| (except in comments)
int main() {
    Vector v1;
    v1.add(0);
    v1.add(1);
    Vector v2 = v1;
    try {
        v1[0] = 2;
        cout << v1[0] << " " << v1[1] << " " << "\n";
        cout << v2[0] << " " << v2[1] << " " << "\n";
    }
    catch (std::runtime_error& e) { cout << e.what(); }
    return 0;
}
