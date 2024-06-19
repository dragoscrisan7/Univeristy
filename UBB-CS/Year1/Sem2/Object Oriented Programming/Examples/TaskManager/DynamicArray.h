#ifndef TASKMANAGER_DYNAMICARRAY_H
#define TASKMANAGER_DYNAMICARRAY_H
#include "Task.h"

template <typename T>
class DynamicVector
{
private:
    T* elems;
    int size;
    int capacity{};

    void Resize(double factor = 2);
public:
    DynamicVector(int capacity = 7);
    ~DynamicVector();

    void add(T task);

    int getSize();
    T& operator[](int index);
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
void DynamicVector<T>::Resize(double factor) {
    this->capacity *= static_cast<int>(factor);

    T* els = new T[this->capacity];
    for(int i=0;i < this->size; i++)
        els[i] = this->elems[i];

    delete[] this->elems;
    this->elems = els;
}

template<typename T>
int DynamicVector<T>::getSize() {
    return this->size;
}

template<typename T>
T &DynamicVector<T>::operator[](int index) {
    if(index < 0 || index >= this->size)
        throw std::out_of_range("Invalid index");
    return this->elems[index];
}

template<typename T>
void DynamicVector<T>::add(T task) {
    if(this->size == this->capacity)
        this->Resize();
    this->elems[this->size] = task;
    this->size++;
}

#endif //TASKMANAGER_DYNAMICARRAY_H
