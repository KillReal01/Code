#include <iostream>
#include "struct.h"

struct node {
	int key;
	unsigned char height;
	node* left;
	node* right;
	node(int k) { key = k; left = right = 0; height = 1; }
};

unsigned char height(node* n);
int balanceFactor(node* n);
void fixHeight(node* n);

node* rightRotate(node*& n);
node* leftRotate(node*& n);
node* balanceNode(node*& n);

node* insertItem(node*& n, int key);
node* findMinItem(node* n);
node* findItem(node* n, int key);
node* removeMinItem(node*& n);
node* removeItem(node*& n, int key);

void deleteTree(node*& n);
void preOrder(node* n);
void inOrder(node* n);
void postOrder(node* n);
void breadthFirst(node* n);

int main() {
	node* root = 0;
	int N = 20;
	for (int i = 0; i < N; i++)
		insertItem(root, rand() % N);

	preOrder(root);
	inOrder(root);
	postOrder(root);
	breadthFirst(root);

	int a = -10, b = findMinItem(root->right)->key;
	(findItem(root, a)) ? std::cout << "\ntree has " << a << "\n" : std::cout << "\ntree hasn't " << a << "\n";
	(findItem(root, b)) ? std::cout << "tree has " << b << "\n\n" : std::cout << "tree hasn't " << b << "\n\n";

	removeItem(root, b);
	removeItem(root, findMinItem(root)->key);

	preOrder(root);
	inOrder(root);
	postOrder(root);
	breadthFirst(root);

	deleteTree(root);
	system("Pause>nul");
	return 0;
}

unsigned char height(node* n) {
	return n ? n->height : 0;
}

int balanceFactor(node* n) {
	return height(n->right) - height(n->left);
}

void fixHeight(node* n) {
	unsigned char hl = height(n->left);
	unsigned char hr = height(n->right);
	n->height = (hl > hr ? hl : hr) + 1;
}

node* rightRotate(node*& n) {// правый поворот вокруг n
	node* tmp = n->left;
	n->left = tmp->right;
	tmp->right = n;
	fixHeight(n);
	fixHeight(tmp);
	n = tmp;
	return tmp;
}

node* leftRotate(node*& n) {// левый поворот вокруг n
	node* tmp = n->right;
	n->right = tmp->left;
	tmp->left = n;
	fixHeight(n);
	fixHeight(tmp);
	n = tmp;
	return tmp;
}

node* balanceNode(node*& n) { // балансировка узла n
	fixHeight(n);
	if (balanceFactor(n) == 2)
	{
		if (balanceFactor(n->right) < 0)
			n->right = rightRotate(n->right);
		return leftRotate(n);
	}
	if (balanceFactor(n) == -2)
	{
		if (balanceFactor(n->left) > 0)
			n->left = leftRotate(n->left);
		return rightRotate(n);
	}
	return n; // балансировка не нужна
}

node* insertItem(node*& n, int key) { // вставка ключа key в дерево с корнем n
	if (!n) {
		n = new node(key);
		return n;
	}
	if (key < n->key)
		n->left = insertItem(n->left, key);
	else if (key > n->key)
		n->right = insertItem(n->right, key);
	return balanceNode(n);
}

node* findMinItem(node* n) { // поиск узла с минимальным ключом в дереве n 
	return n->left ? findMinItem(n->left) : n;
}

node* findItem(node* n, int key) {// поиск узла с ключом key в дереве n 
	while (n) {
		if (key == n->key)
			return n;
		else if (key < n->key)
			n = n->left;
		else
			n = n->right;
	}
	return 0;
}

node* removeMinItem(node*& n) { // удаление узла с минимальным ключом из дерева n
	if (!n->left)
		return n->right;
	n->left = removeMinItem(n->left);
	return balanceNode(n);
}

node* removeItem(node*& n, int key) { // удаление ключа key из дерева n
	if (!n)
		return 0;
	if (key < n->key)
		n->left = removeItem(n->left, key);
	else if (key > n->key)
		n->right = removeItem(n->right, key);
	else //  key == n->key 
	{
		node* l = n->left;
		node* r = n->right;
		delete n;
		if (!r) {
			n = l;
			return l;
		}
		node* min = findMinItem(r);
		min->right = removeMinItem(r);
		min->left = l;
		n = min;
		return balanceNode(min);
	}
	return balanceNode(n);
}

void deleteTree(node*& n) {
	if (n) {
		deleteTree(n->left);
		deleteTree(n->right);
		delete(n);
	}
	n = 0;
}

void preOrder(node* n) {
	myStack* st = 0;
	std::cout << "pre-order: ";
	while (st || n) {
		if (n) {
			std::cout << n->key << " ";
			if (n->right)
				pushStack(st, n->right);
			n = n->left;
		}
		else
			n = popStack(st);
	}
	std::cout << "\n";
}

void inOrder(node* n) {
	myStack* st = 0;
	std::cout << "in-order: ";
	while (st || n) {
		if (n) {
			pushStack(st, n);
			n = n->left;
		}
		else {
			n = popStack(st);
			std::cout << n->key << " ";
			n = n->right;
		}
	}
	std::cout << "\n";
}

void postOrder(node* n) {
	myStack* st = 0;
	node* top = 0, * tmp = 0;
	std::cout << "post-order: ";
	while (st || n) {
		if (n) {
			pushStack(st, n);
			n = n->left;
		}
		else {
			top = topStack(st);
			if (top->right && tmp != top->right) {
				n = top->right;
			}
			else {
				popStack(st);
				std::cout << top->key << " ";
				tmp = top;
			}
		}
	}
	std::cout << "\n";
}

void breadthFirst(node* n) {
	myQueue* q = 0;
	std::cout << "breadth-first: ";
	pushQueue(q, n);
	while (q) {
		node* tmp = frontQueue(q);
		std::cout << tmp->key << " ";
		if (tmp->left)
			pushQueue(q, tmp->left);
		if (tmp->right)
			pushQueue(q, tmp->right);
	}
	std::cout << "\n";
}