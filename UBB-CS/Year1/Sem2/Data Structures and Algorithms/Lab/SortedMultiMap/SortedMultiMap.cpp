#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
	this->relation = r;
	this->cap = 0;
	this->nrElements = 0;
	this->nodes = nullptr;
	this->firstElem = 0;
	this->firstFree = 0;
	alloc(10);
}
//Teta(1)

void SortedMultiMap::alloc(int newCap) {
	SLLANode* newNodes = new SLLANode[newCap];
	if (this->nrElements == 0) {
		for (int i = 0; i < newCap - 1; i++)
		{
			newNodes[i].next = i + 1;
		}
	}
	else {
		int i = this->firstElem;
		while(i != -1) {
			newNodes[i].info.first = this->nodes[i].info.first;
			newNodes[i].info.second = this->nodes[i].info.second;
			newNodes[i].next = this->nodes[i].next;
			i = this->nodes[i].next;
		}
		this->firstFree = this->cap;
		for (int i = this->cap; i < newCap - 1; i++)
			newNodes[i].next = i + 1;
	}
	newNodes[newCap - 1].next = -1;
	this->cap = newCap;
	delete[] this->nodes;
	this->nodes = newNodes;
}
//Teta(newCap)

void SortedMultiMap::add(TKey c, TValue v) {
	auto it = SMMIterator(*this);
	if (this->firstFree == -1) {
		alloc(this->cap * 2);
	}
	this->nodes[this->firstFree].info.first = c;
	this->nodes[this->firstFree].info.second = v;
	int just_added = this->firstFree;
	this->firstFree = this->nodes[this->firstFree].next;
	if (this->nrElements == 0) {
		this->nodes[it.current_element].next = -1;
	}
	else {
		int d;
		it.first();
		while (it.current_element != -1 && !this->relation(c, this->nodes[it.current_element].info.first)) {
			d = it.current_element;
			it.next();
		}
		if (it.current_element == this->firstElem) {
			this->nodes[just_added].next = this->firstElem;
			this->firstElem = just_added;
		}
		else {
			if (it.current_element == -1) {
				this->nodes[d].next = just_added;
				this->nodes[just_added].next = -1;
			}
			else {
				int d_next = this->nodes[d].next;
				this->nodes[d].next = just_added;
				this->nodes[just_added].next = d_next;
			}
		}
	}
	this->nrElements++;
}
//

vector<TValue> SortedMultiMap::search(TKey c) const {
	auto it = SMMIterator(*this);
	it.first();
	auto v = vector<TValue>();
	if (this->isEmpty())
		return v;
	while (it.current_element != -1) {
		if (this->nodes[it.current_element].info.first == c)
			v.push_back(this->nodes[it.current_element].info.second);
		it.next();
	}
	return v;
}

bool SortedMultiMap::remove(TKey c, TValue v) {
	if (this->isEmpty())
		return false;
	auto it = SMMIterator(*this);
	it.first();
	int d = -1;
	while (it.current_element != -1 && (this->nodes[it.current_element].info.first != c || this->nodes[it.current_element].info.second != v)) {
		d = it.current_element;
		it.next();
	}
	if (it.current_element == -1 || this->nrElements == 0)
		return false;
	else {
		if (d == -1) {
			this->firstElem = this->nodes[this->firstElem].next;
		}
		else
		{
			this->nodes[d].next = this->nodes[it.current_element].next;
		}
		this->nodes[it.current_element].next = this->firstFree;
		this->firstFree = it.current_element;
		this->nrElements--;
		return true;
	}
}

//Teta(1)
int SortedMultiMap::size() const {
	return this->nrElements;
}

//Teta(1)
bool SortedMultiMap::isEmpty() const {
	return this->nrElements == 0;
}

//Teta(1)
SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

//Teta(1)
SortedMultiMap::~SortedMultiMap() {
	delete[] this->nodes;
}

//Teta(nrElements)
vector<TValue> SortedMultiMap::valueBag() const{
	auto v = vector<TValue>();
	auto it = SMMIterator(*this);
	it.first();
	while (it.current_element != -1) {
		v.push_back(this->nodes[it.current_element].info.second);
		it.next();
	}
	return v;
}