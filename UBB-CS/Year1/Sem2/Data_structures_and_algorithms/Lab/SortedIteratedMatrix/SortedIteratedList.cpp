#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIteratedList::SLLNode::SLLNode(TComp e, SLLNode* n) {
	info = e;
	next = n;
}
//Teta(1)

SortedIteratedList::SortedIteratedList(Relation r) {
	nrElems = 0;
	relation = r;
	head = nullptr;
}
//Teta(1)

int SortedIteratedList::size() const {
	return nrElems;
}
//Teta(1)

bool SortedIteratedList::isEmpty() const {
	if(head == nullptr)
		return true;
	return false;
}
//Teta(1)

ListIterator SortedIteratedList::first() const {
	return ListIterator(*this);
}
//Teta(1)

TComp SortedIteratedList::getElement(ListIterator poz) const {
	if (poz.current_element == nullptr)
		throw exception();
	return poz.current_element->info;
}
//Teta(1)

TComp SortedIteratedList::remove(ListIterator& poz) {
	if (head == nullptr)
		throw exception();
	if (!poz.valid())
		throw exception();
	TComp value;
	PNode pn = poz.current_element;
	value = pn->info;
	if (pn == head)
		head = pn->next;
	else {
		PNode prevn = head;
		while (prevn->next != pn)
			prevn = prevn->next;
		prevn->next = pn->next;
	}
	poz.current_element = pn->next;
	free(pn);
	nrElems--;
	return value;
}
//BC:Tetha(1) WC:Tetha(nrElements) AC:Tetha(nrElements/2) => complexity O(nrElements)

ListIterator SortedIteratedList::search(TComp e) const{
	//ListIterator l(*this);
	auto l = ListIterator(*this);
	while (l.current_element != nullptr && l.current_element->info != e) {
		l.next();
	}
	return l;
}
//BC:Tetha(1) WC:Tetha(nrElements) AC:Tetha(nrElements/2) => complexity O(nrElements)

void SortedIteratedList::add(TComp e) {
	if(head == nullptr)
		head = new SLLNode(e, nullptr);
	else
	{
		PNode pn;
		pn = head;
		if (!relation(pn->info, e)) {
			head = new SLLNode(e, pn);
		}
		else {
			PNode prvn = nullptr;
			while (pn != nullptr && (relation(pn->info, e))) {
						prvn = pn;			
						pn = pn->next;
					}
			if (pn == nullptr) {
				prvn->next = new SLLNode(e, nullptr);
			}
			else {
				if(prvn == nullptr)
					head = new SLLNode(e, pn);
				else {
					prvn->next = new SLLNode(e, prvn->next);
				}
			}
		}
	}
	nrElems++;
}
//BC:Tetha(1) WC:Tetha(nrElements) AC:Tetha(nrElements/2) => complexity O(nrElements)

SortedIteratedList::~SortedIteratedList() {
	while (head != nullptr)
	{
		PNode p = head;
		head = p->next;
		free(p);
	}
}
//Tetha(nrElements)

ListIterator SortedIteratedList::lastIndexOf(TComp elem) const{
	auto l = ListIterator(*this);
	while (l.current_element != nullptr && l.current_element->info != elem) {
		l.next();
	}
	if (l.current_element != nullptr)
	{
		while (l.current_element->next != nullptr && l.current_element->next->info == elem)
			l.next();
	}
	return l;
}
//BC:Tetha(1) WC:Tetha(nrElements) AC:Tetha(nrElements/2) => complexity O(nrElements)