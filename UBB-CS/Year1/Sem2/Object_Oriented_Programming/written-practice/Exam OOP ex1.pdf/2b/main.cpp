#include <iostream>

using namespace std;

class Ex1 {
public:
    Ex1() { cout << "Exception1 " /*<< "\n*/; }
    Ex1(const Ex1& ex) { cout << "Copy_ex1 " /*<< "\n*/; }
};

class Ex2: public Ex1 {
public:
    Ex2() { cout << "Exception2 " /*<< "\n*/; }
    Ex2(const Ex2& ex) { cout << "Copy_ex2 " /*<< "\n*/; }
};

void except(int x) {
    if (x < 0)
        throw Ex1{};
    else if (x == 0)
        throw Ex2{};
    cout << "Done ";
}

// prints: "Start Exception1 Exception2 Exception1 Copy_ex1 "
// NOTE: I put "\n" in cout statements for flushing the stdout buffer (so I can see with the debugger)
//  switch between w/ and w/o newlines:  - replace between |<< "\n"| and |/*<< "\n*/| (except in comments)
int main() {
    try {
        cout << "Start " /*<< "\n*/; // prints: "Start "
        try {
            except(0); // prints: "Exception1 Exception2 "
        }
        catch (Ex1& e) {}
        except(-2);
    }
    catch (Ex1 e) {}
    return 0;
}
