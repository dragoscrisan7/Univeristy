#pragma once

template <typename T>
class Node {
private:
	T data;
	Node* next;
public:
	Node(const T& _data, Node* _next):data(_data), next(_next) {}
	
	T& getData() {
		return data;
	}
	void setData(T& _data) {
		data = _data;
	}

	Node* getNext() {
		return next;
	}
	void setNext(Node* _next) {
		next = _next;
	}
};

template <typename T>
class LinkedList :public List<T> {
private:
	Node<T>* head;
	int size;

public:
	LinkedList() :head(nullptr), size(0){}
	LinkedList(const LinkedList& other) {
		size = 0;

		head = nullptr;
		
		auto aux = other->head;
		while (aux != nullptr) {
			add(aux->getData());
			aux = aux->next;
			size++;
		}
	}

	~LinkedList() {
		Node<T>* curr_elem;
		while (head != nullptr) {
			curr_elem = head;
			head = head->getNext();
			delete curr_elem;
		}
	}

	LinkedList& operator= (const LinkedList& other) {
		if (this == &other) {
			return *this;
		}
		
		Node<T>* curr_elem; //deleting the old content
		while (head != nullptr) {
			curr_elem = head;
			head = head->next;
			delete curr_elem;
		}

		size = 0; // copy new values
		head = nullptr;
		auto aux = other->head;
		while (aux != nullptr) {
			add(aux->getData());
			aux = aux->next;
			size++;
		}

		return *this;

	}

	T& operator[](int index)const {
		int pos = 0;
		auto parsingNode = head;
		while (pos != index) {
			parsingNode = parsingNode->getNext();
			pos++;
		}
		return parsingNode->getData();
	}
	void add(const T& element) {
		size++;
		auto auxNode = new Node<T>(element, nullptr);
		if (head == nullptr)
		{
			head = auxNode;
		}
		else
		{
			auto parsingNode = head;
			while (parsingNode->getNext() != nullptr) {
				parsingNode = parsingNode->getNext();
			}

			parsingNode->setNext(auxNode);
		}
	}
	int getSize()const {
		return size;
	}
};