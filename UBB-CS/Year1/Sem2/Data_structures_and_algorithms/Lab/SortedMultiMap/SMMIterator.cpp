#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	this->current_element = d.firstElem;
}
//Teta(1)

void SMMIterator::first(){
	this->current_element = map.firstElem;
}
//Teta(1)

void SMMIterator::next(){
	if (!this->valid())
		throw exception();
	else
		this->current_element = map.nodes[this->current_element].next;
}
//Teta(1)

bool SMMIterator::valid() const{
	if (map.isEmpty())
		return false;
	return this->current_element != -1;
}
//Teta(1)

TElem SMMIterator::getCurrent() const{
	if (!this->valid())
		throw exception();
	return map.nodes[this->current_element].info;
}


