#pragma once

typedef std::pair<int, int> TInf;

struct myStack;
void pushItemStack(myStack*& stack, TInf value);
void popItemStack(myStack*& stack);
TInf topItemStack(myStack* stack);
void getLastThreeSubarray(myStack* stack, TInf& x, TInf& y, TInf& z);
