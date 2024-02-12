#pragma once
template <typename T>
class List {
public:
virtual T& operator[](int index)const = 0;
virtual void add(const T& element) = 0;
virtual int getSize()const = 0;
virtual ~List(){}
};