#pragma once

template<class T>
struct node {
	T data;
	node<T>* next;
};

template<class T>
class queue {
private:
	node<T>* begin;
	node<T>* end;
public:
	queue();
	~queue();
	bool is_empty();
	void clear();
	void push(T value);
	void pop();
	T& front();
};

template<class T>
queue<T>::queue() {
	this->begin = nullptr;
	this->end = nullptr;
}

template<class T>
queue<T>::~queue() {
	clear();
}

template<class T>
void queue<T>::clear() {
	node<T>* tmp = 0;
	while (this->begin) {
		if (this->begin)
			tmp = this->begin->next;
		delete this->begin;
		this->begin = tmp;
	}
	this->end = nullptr;
}

template<class T>
bool queue<T>::is_empty() {
	return (!this->begin) ? true : false;
}

template<class T>
void queue<T>::push(T value) {
	node<T>* tmp = new node<T>;
	tmp->data = value;
	tmp->next = nullptr;
	if (this->is_empty())
		this->begin = tmp;
	else if (!this->end) {
		this->begin->next = tmp;
		this->end = tmp;
	}
	else {
		this->end->next = tmp;
		this->end = tmp;
	}
}

template<class T>
void queue<T>::pop() {
	node<T>* tmp = this->begin->next;
	if (this->begin->next == this->end)
		this->end = nullptr;
	delete this->begin;
	this->begin = tmp;
}

template<class T>
T& queue<T>::front() {
	return this->begin->data;
}

template<class T>
class stack {
private:
	node<T>* ptr;
public:
	stack();
	~stack();
	bool is_empty();
	void clear();
	void push(T value);
	void pop();
	T& top();
};

template<class T>
stack<T>::stack() {
	this->ptr = nullptr;
}

template<class T>
stack<T>::~stack() {
	clear();
}

template<class T>
void stack<T>::clear() {
	node<T>* tmp = 0;
	while (this->ptr) {
		if (this->ptr)
			tmp = this->ptr->next;
		delete this->ptr;
		this->ptr = tmp;
	}
}

template<class T>
bool stack<T>::is_empty() {
	return (!this->ptr) ? true : false;
}

template<class T>
void stack<T>::push(T value) {
	node<T> *tmp = new node<T>;
	tmp->data = value;
	tmp->next = this->ptr;
	this->ptr = tmp;
}

template<class T>
void stack<T>::pop() {
	node<T>* tmp = this->ptr->next;
	delete this->ptr;
	this->ptr = tmp;
}

template<class T>
T& stack<T>::top() {
	return this->ptr->data;
}