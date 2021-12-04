#include <iostream>

template<class T>
class vector {
private:
	int size_vector;
	T* data;
public:
	vector();
	vector(int size);
	vector(int size, T value);
	~vector();//деструктор
	vector(vector& other);

	int size();//размер вектора
	void resize(int size);
	void resize(int size, T value);
	bool empty();
	T& operator[] (const int index);
	vector& operator = (const vector& other);
	void push_back(T value);
	void pop_back();
	void insert(T value);
	void insert(T* it, T value);
	void insert(T* it, int n, T value);
	const T front();
	const T back();
	void erase(T* it);
	void erase(T* begin, T* end);
	void clear();
	void swap(vector& tmp);

	T* begin();
	T* end();
	void printVector();
};

int main() {
	vector<int> a, b(10,5);
	a.swap(b);
	a.printVector();
	b.printVector();
	return 0;
}

template<class T>
vector<T>::vector() {
	this->size_vector = 0;
	this->data = nullptr;
}

template<class T>
vector<T>::vector(int size) {
	this->size_vector = size;
	data = new T[size];
	for (int i = 0; i < size; i++) {
		this->data[i] = 0;
	}
}

template<class T>
vector<T>::vector(int size, T value) {
	this->size_vector = size;
	data = new T[size];
	for (int i = 0; i < size; i++) {
		this->data[i] = value;
	}
}

template<class T>
vector<T>::~vector() {
	delete[] this->data;
}

template<class T>
vector<T>::vector(vector& other) {
	this->data = new T[other.size_vector];
	for (int i = 0; i < other.size_vector; i++) {
		data[i] = other.data[i];
	}
	this->size_vector = other.size_vector;
}

template<class T>
int vector<T>::size() {
	return this->size_vector;
}

template<class T>
T& vector<T>::operator[] (const int index) {
	return this->data[index];
}

template<class T>
vector<T>& vector<T>::operator = (const vector& other) {
	if (!this) {
		delete[] this->data;
		this->data = new T[other.size_vector];
		this->size_vector = other.size_vector;
		for (int i = 0; i < other.size_vector; i++) {
			data[i] = other.data[i];
		}
	}
	return *this;
 }

template<class T>
void vector<T>::resize(int size) {
	T* tmp = new T[size];
	int min = (size < this->size_vector) ? size : this->size_vector;
	int max = (size > this->size_vector) ? size : this->size_vector;
	memcpy(tmp, this->data, min * sizeof(T));
	if (min != size) {
		for (int i = min; i < max; i++) {
			tmp[i] = 0;
		}
	}
	delete[] this->data;
	this->data = tmp;
	this->size_vector = size;
}

template<class T>
void vector<T>::resize(int size, T value) {
	T* tmp = new T[size];
	int min = (size < this->size_vector) ? size : this->size_vector;
	int max = (size > this->size_vector) ? size : this->size_vector;
	memcpy(tmp, this->data, min * sizeof(T));
	if (min != size) {
		for (int i = min; i < max; i++) {
			tmp[i] = value;
		}
	}
	delete[] this->data;
	this->data = tmp;
	this->size_vector = size;
}

template<class T>
void vector<T>::printVector() {
	for (int i = 0; i < this->size_vector; i++)
		std::cout << this->data[i] << " ";
	std::cout << "\n";
}

template<class T>
bool vector<T>::empty() {
	return (!this->size_vector) ? true : false;
}

template<class T>
void vector<T>::push_back(T value) {
	T* tmp = this->data;
	this->data = new T[size_vector + 1];
	for (int i = 0; i < size_vector; i++) {
		this->data[i] = tmp[i];
	}
	this->data[size_vector] = value;
	delete[] tmp;
	this->size_vector++;
}

template<class T>
void vector<T>::pop_back() {
	T* tmp = data;
	this->data = new T[size_vector - 1];
	for (int i = 0; i < size_vector - 1; i++) {
		this->data[i] = tmp[i];
	}
	delete[] tmp;
	this->size_vector--;
}

template<class T>
void vector<T>::insert(T value) {
	T* tmp = new T[this->size_vector + 1];
	memcpy(tmp + 1, this->data, this->size_vector * sizeof(T));
	tmp[0] = value;
	delete[] this->data;
	this->data = tmp;
	this->size_vector++;
}

template<class T>
void vector<T>::insert(T* it, int n, T value) {
	T* tmp = new T[this->size_vector + n];
	int count = it - this->begin();
	memcpy(tmp, this->data, count * sizeof(T));
	for (int i = count; i < n + it - this->begin(); i++) {
		tmp[i] = value;
	}
	memcpy(tmp + count + n, this->data + count, (this->size_vector - count) * sizeof(T));
	delete[] this->data;
	this->data = tmp;
	this->size_vector += n;
}

template<class T>
void vector<T>::insert(T* it, T value) {
	T* tmp = new T[this->size_vector + 1];
	int count = it - this->begin();
	memcpy(tmp, this->data, count * sizeof(T));
	tmp[count] = value;
	memcpy(tmp + count + 1, this->data + count, (this->size_vector - count) * sizeof(T));
	delete[] this->data;
	this->data = tmp;
	this->size_vector++;
}

template<class T>
void vector<T>::erase(T* it) {
	T* tmp = new T[this->size_vector - 1];
	int count = it - this->begin();
	memcpy(tmp, this->data, count * sizeof(T));
	memcpy(tmp + count, this->data + count + 1, (this->size_vector - count - 1) * sizeof(T));
	delete[] this->data;
	this->data = tmp;
	this->size_vector--;
}

template<class T>
void vector<T>::erase(T* begin, T* end) {
	int sub = end - begin, count = begin - this->begin();
	T* tmp = new T[this->size_vector - sub];
	memcpy(tmp, this->data, (begin - this->begin()) * sizeof(T));
	memcpy(tmp + count, this->data + (end - this->data), (this->size_vector - sub - count) * sizeof(T));
	delete[] this->data;
	this->data = tmp;
	this->size_vector -= sub;
}

template<class T>
const T vector<T>::front() {
	return this->data[0];
}

template<class T>
const T vector<T>::back() {
	return this->data[this->size_vector - 1];
}

template<class T>
void vector<T>::clear() {
	delete[] this->data;
	this->data = nullptr;
	this->size_vector = 0;
}

template<class T>
void vector<T>::swap(vector& other) {
	vector<T> tmp(*this);
	*this = other;
	other = tmp;
}

template<class T>
T* vector<T>::begin() {
	return this->data;
}

template<class T>
T* vector<T>::end() {
	return this->data + this->size_vector;
}
