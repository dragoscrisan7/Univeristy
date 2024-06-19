#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
template <typename T>

class Adder{
private:
    std::vector<T> elems;
public:
    Adder(T val){elems.push_back(val);}
    Adder& operator+(const T& val){
        elems.push_back(val);
        return *this;
    }
    Adder& operator++(){
        elems.push_back(elems[elems.size()-1]);
        return *this;
    }
    Adder& operator--(){
        if(!elems.empty()) {
            elems.pop_back();
            return *this;
        }
        else{
            throw std::runtime_error("no more values\n");
        }
    }

    T sum(){
        T aux = 0;
        for(auto el:elems){
            aux += el;
        }
        return aux;
    }
};

class B{
public:
    B() {}
    B(const B &b){cout << "copy";}
    virtual void f() {cout<< "B.f";}
    void g(B b){cout<<"B.g";}
    virtual ~B() {cout<<"~B";}
};
class D: public B{
public:
    D(){}
    void f(){B::f();cout<<"D.f";}
    void g(D d){B::g(d); cout<<"D.g";}
};

class A{
private:
    int *x;
public:
    A(int _x = 0){
        x = new int{ _x };
    }
    A(const A& a){
        x = new int{*a.x};
    }
    int get(){return *x;}
    void set(int _x){*x = _x;}
    ~A() {delete x;}
};
