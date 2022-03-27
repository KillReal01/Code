#pragma once

struct node;
struct myStack;
struct myQueue;

void pushStack(myStack*& stack, node* value);
node* popStack(myStack*& stack);
node* topStack(myStack* stack);

void pushQueue(myQueue*& q, node* value);
node* frontQueue(myQueue*& q);