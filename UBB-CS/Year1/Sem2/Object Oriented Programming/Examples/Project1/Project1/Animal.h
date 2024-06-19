#pragma once
class Animal
{
private:
	int age;

public:
	Animal(int a);

	virtual void speak();
	virtual ~Animal() {}
};

