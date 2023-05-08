#include <iostream>
#include "structures.h"

struct myStack {
	TInf value;
	myStack* next;
};

void pushItemStack(myStack*& stack, TInf value) {
	myStack* tmp = new myStack;
	tmp->value = value;
	tmp->next = stack;
	stack = tmp;
}

void popItemStack(myStack*& stack) {
	myStack* del = stack;
	if (stack) {
		stack = stack->next;
		delete del;
	}
}

TInf topItemStack(myStack* stack) {
	return stack->value;
}

void getLastThreeSubarray(myStack* stack, TInf& x, TInf& y, TInf& z) {
	if (stack) {
		x.second = topItemStack(stack).second;
		x.first = topItemStack(stack).first;
		if (stack->next) {
			y.second = topItemStack(stack->next).second;
			y.first = topItemStack(stack->next).first;
			if (stack->next->next) {
				z.second = topItemStack(stack->next->next).second;
				z.first = topItemStack(stack->next->next).first;
			}
			else z.second = 0;
		}
		else y.second = 0;
	}
}
