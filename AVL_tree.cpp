#include <iostream>

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
void printTree(node* n);

int main() {
	node* root = 0;
	int N = 10;
	int* arr = new int[N];
	for (int i = 0; i < N; i++) {
		arr[i] = rand() % 10;
		insertItem(root, arr[i]);
	}
	removeItem(root, 1);
	removeItem(root, -1);
	insertItem(root, -1);
	insertItem(root, 15);
	printTree(root);

	int a = 10, b = findMinItem(root)->key;
	(findItem(root, a)) ? std::cout << "\ntree has " << a: std::cout << "\ntree hasn't " << a;
	(findItem(root, b)) ? std::cout << "\ntree has " << b : std::cout << "\ntree hasn't " << b;

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

void printTree(node* n) {
	if (n) {
		printTree(n->left);
		std::cout << n->key << " ";
		printTree(n->right);
	}
}
