#pragma once
#include "SortedIteratedList.h"

//DO NOT CHANGE THIS PART
class ListIterator{
	friend class SortedIteratedList;
private:
	ListIterator(const SortedIteratedList& list);

	const SortedIteratedList& list;
	SortedIteratedList::PNode current_element;
public:
	void first();
	void next();
	bool valid() const;
    TComp getCurrent() const;
};


