#include <iostream>

template<class T>
class matrix {
private:
	int line, column, ** data;
public:
	matrix();
	matrix(int line, int column);
	matrix(int line, int column, T value);
	matrix(int size);//E
	~matrix();
	matrix(matrix& other);

	void set();
	void set(T value);
	void size();//размер массива
	void clear();
	void printMatrix();
	void swap(matrix& tmp);

	T* operator[] (const int index);
	matrix& operator = (const matrix& other);
	matrix operator + (const matrix& other);
	matrix operator - (const matrix& other);
	matrix operator * (const matrix& other);
	matrix operator * (const int value);
	matrix operator ^ (const int value);
};

int main() {
	matrix <int> a(3, 3, 2);
	//a.printMatrix();
	matrix <int> b(3, 3, 3), c;
	a.printMatrix();
	b.printMatrix();
	c = (a ^ 5) - (a * 2) + (b * 4) + (b ^ 3) - ((b * 2) ^ 5);
	a.printMatrix();
	b.printMatrix();
	c.printMatrix();
	return 0;
}

template<class T>
matrix<T>::matrix() {
	this->column = 0;
	this->line = 0;
	this->data = 0;
}

template<class T>
matrix<T>::matrix(int size) {
	this->line = size;
	this->column = size;
	this->data = new T * [size];
	for (int i = 0; i < size; i++) {
		this->data[i] = new T[size];
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			(i == j) ? this->data[i][j] = 1 : this->data[i][j] = 0;
		}
	}
}

template<class T>
matrix<T>::matrix(int line, int column) {
	this->line = line;
	this->column = column;
	this->data = new T * [line];
	for (int i = 0; i < line; i++) {
		this->data[i] = new T[column];
	}
	for (int i = 0; i < line; i++) {
		for (int j = 0; j < column; j++) {
			this->data[i][j] = 0;
		}
	}
}

template<class T>
matrix<T>::matrix(int line, int column, T value) {
	this->line = line;
	this->column = column;
	this->data = new T * [line];
	for (int i = 0; i < line; i++) {
		this->data[i] = new T[column];
	}
	for (int i = 0; i < line; i++) {
		for (int j = 0; j < column; j++) {
			this->data[i][j] = value;
		}
	}
}

template<class T>
matrix<T>::~matrix() {
	for (int i = 0; i < line; i++) {
		delete this->data[i];
	}
	delete[] this->data;
	this->line = 0;
	this->column = 0;
}

template<class T>
matrix<T>::matrix(matrix& other) {
	this->data = new T * [other.line];
	for (int i = 0; i < other.line; i++) {
		this->data[i] = new T[other.column];
	}
	this->line = other.line;
	this->column = other.column;
	for (int i = 0; i < other.line; i++) {
		memcpy(this->data[i], other.data[i], other.column * sizeof(T));
	}
}

template<class T>
void matrix<T>::set() {
	clear();
	std::cout << "Enter the numbers of lines and columns: ";
	std::cin >> this->line >> this->column;
	this->data = new T * [this->line];
	for (int i = 0; i < this->line; i++) {
		this->data[i] = new T[this->column];
	}
	std::cout << "Enter values:\n";
	for (int i = 0; i < this->line; i++) {
		for (int j = 0; j < this->column; j++) {
			std::cin >> this->data[i][j];
		}
	}
}

template<class T>
void matrix<T>::set(T value) {
	clear();
	std::cout << "Enter the numbers of lines and columns: ";
	std::cin >> this->line >> this->column;
	this->data = new T * [this->line];
	for (int i = 0; i < this->line; i++) {
		this->data[i] = new T[this->column];
	}
	for (int i = 0; i < this->line; i++) {
		for (int j = 0; j < this->column; j++) {
			this->data[i][j] = value;
		}
	}
}

template<class T>
void matrix<T>::size() {
	std::cout << "matrix has " << this->line << " lines and "
		<< this->column << " columns\n";
}

template<class T>
T* matrix<T>::operator[] (const int index) {
	return this->data[index];
}

template<class T>
void matrix<T>::printMatrix() {
	std::cout << "Matrix:\n";
	for (int i = 0; i < this->line; i++) {
		for (int j = 0; j < this->column; j++)
			std::cout << this->data[i][j] << " ";
		std::cout << "\n";
	}
	std::cout << "\n";
}

template<class T>
void matrix<T>::clear() {
	for (int i = 0; i < this->line; i++) {
		delete this->data[i];
	}
	delete[] this->data;
	this->line = 0;
	this->column = 0;
	this->data = 0;
}

template<class T>
matrix<T>& matrix<T>::operator = (const matrix& other) {
	clear();
	this->data = new T * [other.line];
	for (int i = 0; i < other.line; i++) {
		this->data[i] = new T[other.column];
	}
	this->line = other.line;
	this->column = other.column;
	for (int i = 0; i < other.line; i++) {
		memcpy(this->data[i], other.data[i], other.column * sizeof(T));
	}
	return *this;
}

template<class T>
matrix<T> matrix<T>::operator + (const matrix& other) {
	matrix<T> tmp(*this);
	if (this->line == other.line && this->column == other.column) {
		for (int i = 0; i < this->line; i++) {
			for (int j = 0; j < this->column; j++) {
				tmp.data[i][j] += other.data[i][j];
			}
		}
	}
	else {
		std::cout << "We can not add!\n";
	}
	return tmp;
}

template<class T>
matrix<T> matrix<T>::operator - (const matrix& other) {
	matrix<T> tmp(*this);
	if (this->line == other.line && this->column == other.column) {
		for (int i = 0; i < this->line; i++) {
			for (int j = 0; j < this->column; j++) {
				tmp.data[i][j] -= other.data[i][j];
			}
		}
	}
	else {
		std::cout << "We can not subtract!\n";
	}
	return tmp;
}

template<class T>
matrix<T> matrix<T>::operator * (const matrix& other) {
	if (this->column == other.line) {
		matrix<T> tmp(this->line, other.column);
		for (int i = 0; i < this->line; i++) {
			for (int j = 0; j < other.column; j++) {
				for (int k = 0; k < this->column; k++) {
					tmp.data[i][j] += this->data[i][k] * other.data[k][j];
				}
			}
		}
		return tmp;
	}
	else {
		std::cout << "We can not multiply!\n";
		return 0;
	}
}

template<class T>
matrix<T> matrix<T>::operator * (const int value) {
	matrix<T> tmp(*this);
	for (int i = 0; i < this->line; i++) {
		for (int j = 0; j < this->column; j++) {
			tmp.data[i][j] *= value;
		}
	}
	return tmp;
}

template<class T>
matrix<T> matrix<T>::operator ^ (const int value) {
	if (this->column == this->line) {
		matrix<T> tmp(this->column);
		for (int i = 0; i < value; i++) {
			tmp = (*this) * tmp;
		}
		return tmp;
	}
	else {
		std::cout << "We can not raise to the power!\n";
		return 0;
	}
}

template<class T>
void matrix<T>::swap(matrix& other) {
	matrix<T> tmp(*this);
	*this = other;
	other = tmp;
}



