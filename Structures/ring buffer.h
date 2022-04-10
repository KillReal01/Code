#pragma once

//// ring buffer list
template<class T>
struct node {
	T data;
	node<T>* next;
};

template<class T>
class list {
private:
	node<T>* head = nullptr;
	node<T>* tail = nullptr;
	int size_ = 0;
public:
	~list() {
		node<T>* tmp;
		for (int i = 0; i < size_; i++) {
			tmp = head->next;
			delete head;
			head = tmp;
		}
		head = nullptr;
		tail = nullptr;
		size_ = 0;
	}

	bool isEmpty() {
		return (!head) ? true : false;
	}

	void push_back(T data) {
		node<T>* tmp = new node<T>;
		if (isEmpty()) {
			head = tmp;
		}
		else {
			tail->next = tmp;
		}
		tail = tmp;
		*tmp = { data, head };
		size_++;
	}

	void push_front(T data) {
		node<T>* tmp = new node<T>;
		tmp->data = data;
		if (isEmpty()) {
			tail = tmp;
			tmp->next = tail;
		}
		else {
			tail->next = tmp;
			tmp->next = head;
		}
		head = tmp;
		size_++;
	}

	void pop_back() {
		node<T>* tmp, * del;
		tmp = head;
		del = tail;
		if (!isEmpty()) {
			if (head != tail) {
				while (tmp->next != tail) {
					tmp = tmp->next;
				}
				delete del;
				tmp->next = head;
				tail = tmp;
			}
			else {
				delete del;
				head = nullptr;
				tail = nullptr;
			}
		}
		size_--;
	}

	void pop_front() {
		node<T>* tmp, * del;
		tmp = head->next;
		del = head;
		if (!isEmpty()) {
			if (head != tail) {
				delete del;
				tail->next = tmp;
				head = tmp;
			}
			else {
				delete del;
				head = nullptr;
				tail = nullptr;
			}
		}
		size_--;
	}

	int size() {
		return size_;
	}

	T front() {
		return head->data;
	}

	T back() {
		return tail->data;
	}
};

//// ring buffer vector
template<typename T>
class vector {
private:
	T* arr_ = nullptr;
	int size_ = 0;
	int capacity_ = 1;

	void increase() {
		capacity_ *= 2;
		T* tmp = arr_;
		arr_ = new T[capacity_];
		for (int i = 0; i < size_; ++i) {
			arr_[i] = tmp[i];
		}
		delete[] tmp;
	}
public:
	vector() {
		arr_ = new T[1];
	}
	vector(vector& other) {
		if (this != &other) {
			delete[] arr_;
			arr_ = other.arr_;
			size_ = other.size_;
			capacity_ = other.capacity_;
			other.arr_ = nullptr;
			other.size_ = other.capacity_ = 0;
		}
	}
	~vector() {
		delete[] arr_;
		arr_ = new T[1];
		size_ = 0;
		capacity_ = 1;
	}

	bool isEmpty() {
		return size_ == 0;
	}

	int size() {
		return size_;
	}

	int capacity() {
		return capacity_;
	}

	void pushBack(const T& value) {
		if (size_ >= capacity_) increase();
		arr_[size_++] = value;
	}

	void remove(int index) {
		for (int i = index + 1; i < size_; ++i) {
			arr_[i - 1] = arr_[i];
		}
		--size_;
	}

	T* front() {
		return &arr_[0];
	}

	T* back() {
		return &arr_[size_];
	}

	T& operator[](int index) {
		return arr_[index % size_];
	}
};