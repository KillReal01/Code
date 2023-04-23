#include "square_matrix.h"
#include <math.h>

TSquareMatrix::TSquareMatrix()
    : TMatrix()
{}

TSquareMatrix::TSquareMatrix(int n)
    : TMatrix(n, n)
{}

TSquareMatrix::TSquareMatrix(int n, QByteArray &arr)
    : TMatrix(n, n, arr)
{}

TSquareMatrix::TSquareMatrix(const TSquareMatrix& other) {
	this->row = other.row;
	this->mtx = this->allocate_memory(this->row, this->row);

	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->row; j++) {
			this->mtx[i][j] = other.mtx[i][j];
		}
	}
}

void TSquareMatrix::set() {
	this->clear();

	std::cout << "Enter dimension: ";
	std::cin >> this->row;

	std::cout << "Enter matrix:\n";

	mtx = this->allocate_memory(this->row, this->row);
	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->row; j++) {
			std::cin >> mtx[i][j];
		}
	}
}

void TSquareMatrix::transpose() {
	for (int i = 0; i < this->row; i++) {
		for (int j = i; j < this->row; j++) {
			std::swap(this->mtx[i][j], this->mtx[j][i]);
		}
	}
}

std::ostream& operator<<(std::ostream& os, TSquareMatrix& a) {
	for (int i = 0; i < a.row; i++) {
		for (int j = 0; j < a.row; j++) {
			os << a.mtx[i][j] << " ";
		}
		os << "\n";
	}
	return os;
}

QString& operator<<(QString& s, TSquareMatrix& c)
{
	int n = c.row;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			s << c.mtx[i][j];
		}
	}
	return s;
}

TSquareMatrix TSquareMatrix::triangle_matrix() {
	TSquareMatrix a(*this);
	int n = a.row;

	int countSwaps = 1;
	double eps = 1.0e-6;

	for (int i = 0; i < n; ++i) {
		
		int iMax = i;
		for (int j = i + 1; j < n; ++j)
			if (abs(a.mtx[j][i]) > abs(a.mtx[iMax][i]))
				iMax = j;
		if (abs(a.mtx[iMax][i]) < eps) {
			continue;
		}
		for (int k = 0; k < n; ++k)
			std::swap(a.mtx[i][k], a.mtx[iMax][k]);
		countSwaps = -countSwaps * (i != iMax ? 1 : -1);

		
		for (int j = i + 1; j < n; ++j) {
			number q = -a.mtx[j][i] / a.mtx[i][i];
			for (int k = n - 1; k >= i; --k)
				a.mtx[j][k] = a.mtx[j][k] + q * a.mtx[i][k];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (abs(a.mtx[i][j]) < eps)
				a.mtx[i][j] = number(0);
		}
	}

	a.mtx[0][0] = a.mtx[0][0] * countSwaps;
	return a;
}

number TSquareMatrix::det() {
	TSquareMatrix a = this->triangle_matrix();
	number det = a.mtx[0][0];
	for (int i = 1; i < a.row; i++) {
		if (a.mtx[i][i] == number(0))
			return number(0);
		det = det * a.mtx[i][i];
	}
	return det;
}

int TSquareMatrix::rank() {
	TSquareMatrix a = this->triangle_matrix();
	for (int i = this->row - 1; i >= 0; i--) {
		for (int j = 0; j < this->row; j++) {
			if (a.mtx[i][j] != number(0))
				return i + 1;
		}
	}
	return 0;
}
