#include <iostream>
#include "struct.h"

struct node {
	int key;
	unsigned char height;
	node* left;
	node* right;
	node(int k) { key = k; left = right = 0; height = 1; }
};

struct myStack {
	node* value;
	myStack* next;
};

struct myQueue {
	node* value;
	myQueue* next, * prev;
};

void pushStack(myStack*& stack, node* value) {
	myStack* tmp = new myStack;
	tmp->value = value;
	tmp->next = stack;
	stack = tmp;
}

node* popStack(myStack*& stack) {
	myStack* del = stack;
	node* tmp = stack->value;
	if (stack) {
		stack = stack->next;
		delete del;
		return tmp;
	}
	return 0;
}

node* topStack(myStack* stack) {
	return stack->value;
}

void pushQueue(myQueue*& q, node* value) {
	myQueue* tmp = new myQueue;
	tmp->value = value;
	if (q) {
		myQueue* tail = q->prev;
		if (tail) {
			tail->next = tmp;
			tmp->prev = tail;
		}
		else {
			q->next = tmp;
			tmp->prev = q;
		}
		q->prev = tmp;
		tmp->next = q;
	}
	else {
		q = tmp;
		q->next = 0;
		q->prev = 0;
	}
}

node* frontQueue(myQueue*& q) {
	if (q) {
		myQueue* del = q, * tail = q->prev;
		node* tmp = q->value;

		q = q->next;
		if (tail && q != tail) {//> 2 items
			q->prev = tail;
			tail->next = q;
		}
		else if (tail && q == tail) {//2 items
			q->prev = 0;
			q->next = 0;
		}
		delete del;
		return tmp;
	}
	return 0;
}



