#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

ListIterator::ListIterator(const SortedIteratedList& l) : list(l){
	current_element = l.head;
}
//Tetha(1)

void ListIterator::first(){
	current_element = list.head;
}
//Tetha(1)

void ListIterator::next(){
	if (current_element == nullptr) throw exception();
	current_element = current_element->next;
}
//Tetha(1)

bool ListIterator::valid() const{
	return current_element != nullptr;
}
//Tetha(1)

TComp ListIterator::getCurrent() const{

	if (current_element == nullptr) throw exception();
	return current_element->info;
}
//Tetha(1)


