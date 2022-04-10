#pragma once

template<class T>
class vector {
private:
	int size_vector;
	T* data;
public:
	vector();
	vector(int size);
	vector(int size, T value);
	~vector();
	vector(const vector& other);

	int size();
	bool empty();
	T& operator[] (const int index);
	vector& operator = (const vector& other);
	void push_back(T value);
	void pop_back();
	const T front();
	const T back();
	void clear();

	T* begin();
	T* end();
};


template<class T>
vector<T>::vector() {
	size_vector = 0;
	data = nullptr;
}

template<class T>
vector<T>::vector(int size) {
	size_vector = size;
	data = new T[size];
	for (int i = 0; i < size; i++) {
		this->data[i] = 0;
	}
}

template<class T>
vector<T>::vector(int size, T value) {
	size_vector = size;
	data = new T[size];
	for (int i = 0; i < size; i++) {
		data[i] = value;
	}
}

template<class T>
vector<T>::~vector() {
	delete[] data;
}

template<class T>
vector<T>::vector(const vector& other) {
	data = new T[other.size_vector];
	for (int i = 0; i < other.size_vector; i++) {
		data[i] = other.data[i];
	}
	size_vector = other.size_vector;
}

template<class T>
int vector<T>::size() {
	return size_vector;
}

template<class T>
T& vector<T>::operator[] (const int index) {
	return data[index];
}

template<class T>
vector<T>& vector<T>::operator = (const vector& other) {
	if (!this) {
		delete[] this->data;
		data = new T[other.size_vector];
		size_vector = other.size_vector;
		for (int i = 0; i < other.size_vector; i++) {
			data[i] = other.data[i];
		}
	}
	return *this;
}


template<class T>
bool vector<T>::empty() {
	return (!size_vector) ? true : false;
}

template<class T>
void vector<T>::push_back(T value) {
	T* tmp = data;
	data = new T[size_vector + 1];
	for (int i = 0; i < size_vector; i++) {
		data[i] = tmp[i];
	}
	data[size_vector] = value;
	delete[] tmp;
	size_vector++;
}

template<class T>
void vector<T>::pop_back() {
	T* tmp = data;
	data = new T[size_vector - 1];
	for (int i = 0; i < size_vector - 1; i++) {
		data[i] = tmp[i];
	}
	delete[] tmp;
	size_vector--;
}


template<class T>
const T vector<T>::front() {
	return this->data[0];
}

template<class T>
const T vector<T>::back() {
	return data[size_vector - 1];
}

template<class T>
void vector<T>::clear() {
	delete[] this->data;
	data = nullptr;
	size_vector = 0;
}

template<class T>
T* vector<T>::begin() {
	return data;
}

template<class T>
T* vector<T>::end() {
	return data + size_vector;
}
