#include <iostream>
#include <stdio.h>
#include <string>

//реализаци€ стека
struct Stack {
	char value;
	Stack* Next;
};
void Push(Stack*& Beg, char value);
void Pop(Stack*& Beg);
char Top(Stack* Beg);

//ѕрочее
int Prioritet(char c);

int main() {
	Stack* Stack = 0;
	std::string input, output = "", part;
	int pos = 0;
	char tmp;

	std::cout << "Enter all elements with spaces\n\nExample: ( 3 + 2 ) * 4\n\n";
	getline(std::cin, input);

	while (pos != -1) {//читаем строку
		pos = input.find(" ");
		part = input.substr(0, pos);
		input.erase(0, pos + 1);
		tmp = part[0];
		
		if (tmp >= '0' && tmp <= '9') {//если операнд
			output = output + part + ' ';
		}
		else if (tmp == '(') {//если открывающа€ скобка
			Push(Stack, tmp);
		}

		else if (tmp == ')') {//если закрывающа€ скобка
			while (Top(Stack) != '(') {
				output = output + Top(Stack) + ' ';
				Pop(Stack);
			}
			Pop(Stack);//удал€ем '('
		}

		else if (tmp == '+' || tmp == '-' || tmp == '*' || tmp == '/') {//если операци€

			if (Stack) {
				while (Prioritet(Top(Stack)) >= Prioritet(tmp)) {
					output = output + Top(Stack) + ' ';
					Pop(Stack);
					if (!Stack) {
						break;
					}
				}
			}
			Push(Stack, tmp);
		}

	}

	while (Stack) {//оставшиес€ операции в стеке пишем в выходную строку
		output = output + Top(Stack) + ' ';
		Pop(Stack);
	}

	std::cout << output;
	return 0;
}

void Push(Stack*& Beg, char value) {
	Stack* New = new Stack;
	New->value = value;
	New->Next = Beg;
	Beg = New;
}

void Pop(Stack*& Beg) {
	Stack* Del = Beg;
	char value;
	if (Beg) {
		Beg = Beg->Next;
		value = Del->value;
		delete Del;
	}
}

char Top(Stack* Beg) {
	return Beg->value;
}

int Prioritet(char c) {
	switch (c) {
	case '(': return 1;
	case '+': case '-': return 2;
	case '*': case '/': return 3;
	default: return 0;
	}
}