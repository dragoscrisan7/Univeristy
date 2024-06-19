#ifndef A5_6_DRAGOSCRISAN7_DYNAMIC_ARRAY_H
#define A5_6_DRAGOSCRISAN7_DYNAMIC_ARRAY_H
#include "Dog.h"

template <typename T>
class DynamicVector
{
private:
    T* elems;
    int size;
    int capacity{};

    // Resizes the current DynamicVector, multiplying its capacity by a given factor (real number).
    void resize(double factor = 2);
public:
    //default constructor of the dynamic vector
    DynamicVector(int capacity = 7);
    //destructor for the dynamic vector
    ~DynamicVector();

    //assign operator for the dynamic vector
    DynamicVector& operator=(const DynamicVector& v);

    // Adds an element to the current DynamicVector.
    void add(T e);
    // Deletes an element from the current Dynamic Vector.
    void del(int del_index);
    // Updates an element from the current Dynamic Vector.
    void update(int update_index,T e);

    //[] operator for the dynamic vector
    T& operator[](int index);

    //Returns the size of the current vector(the number of elements it holds)
    int getSize() const;
};


template <typename T>
DynamicVector<T>::DynamicVector(int capacity)
{
    size = 0;
    this->capacity = capacity;
    this->elems = new T[capacity];
}

template <typename T>
DynamicVector<T>::~DynamicVector()
{
    delete[] this->elems;
}

template <typename T>
DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector<T>& v)
{
    if (this == &v)
        return *this;

    this->size = v.size;
    this->capacity = v.capacity;

    delete[] this->elems;
    this->elems = new T[this->capacity];
    for (int i = 0; i < this->size; i++)
        this->elems[i] = v.elems[i];

    return *this;
}

template <typename T>
void DynamicVector<T>::add(T e)
{
    if (this->size == this->capacity)
        this->resize();
    this->elems[this->size] = e;
    this->size++;
}
template <typename T>
void DynamicVector<T>::del(const int del_index)
{
    if(del_index == this->size-1)
        this->size--;
    else {
        this->elems[del_index] = this->elems[this->size - 1];
        this->size--;
    }
}
template <typename T>
void DynamicVector<T>::update(int update_index,T e)
{
    this->elems[update_index] = e;
}

template <typename T>
void DynamicVector<T>::resize(double factor)
{
    this->capacity *= static_cast<int>(factor);

    T* els = new T[this->capacity];
    for (int i = 0; i < this->size; i++)
        els[i] = this->elems[i];

    delete[] this->elems;
    this->elems = els;
}

template <typename T>
int DynamicVector<T>::getSize() const
{
    return this->size;
}

template <typename T>
T& DynamicVector<T>::operator[](int index)
{
    if(index < 0 || index >= this->size)
        throw std::out_of_range("index err");
    return this->elems[index];
}

#endif //A5_6_DRAGOSCRISAN7_DYNAMIC_ARRAY_H
