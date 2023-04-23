#ifndef TSQUARE_MATRIX_H
#define TSQUARE_MATRIX_H

#include <iostream>
#include "matrix.h"
#include <math.h>

template<class number>
class TSquareMatrix : public TMatrix<number>
{
public:
    TSquareMatrix();
    TSquareMatrix(int);
    TSquareMatrix(const TSquareMatrix<number> &);
    TSquareMatrix(int, QByteArray &);

    number det();
    int rank();
    void transpose() override;
    void set() override;

    template<class T>
    friend std::ostream &operator<<(std::ostream &, TSquareMatrix<T> &);

    template<class T>
    friend QString &operator<<(QString &s, TSquareMatrix<T> &c);

private:
    TSquareMatrix<number> triangle_matrix();
};

template<class number>
TSquareMatrix<number>::TSquareMatrix()
    : TMatrix<number>()
{}

template<class number>
TSquareMatrix<number>::TSquareMatrix(int n)
    : TMatrix<number>(n, n)
{}

template<class number>
TSquareMatrix<number>::TSquareMatrix(int n, QByteArray &arr)
    : TMatrix<number>(n, n, arr)
{}

template<class number>
TSquareMatrix<number>::TSquareMatrix(const TSquareMatrix<number>& other) {
    this->row = other.row;
    this->mtx = this->allocate_memory(this->row, this->row);

    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->row; j++) {
            this->mtx[i][j] = other.mtx[i][j];
        }
    }
}

template<class number>
void TSquareMatrix<number>::set() {
    this->clear();

    std::cout << "Enter dimension: ";
    std::cin >> this->row;

    std::cout << "Enter matrix:\n";

    this->mtx = this->allocate_memory(this->row, this->row);
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->row; j++) {
            std::cin >> this->mtx[i][j];
        }
    }
}

template<class number>
void TSquareMatrix<number>::transpose() {
    for (int i = 0; i < this->row; i++) {
        for (int j = i; j < this->row; j++) {
            std::swap(this->mtx[i][j], this->mtx[j][i]);
        }
    }
}

template<class number>
std::ostream &operator<<(std::ostream &os, TSquareMatrix<number> &c)
{
    int n = c.row;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            os << c.mtx[i][j] << " ";
        }
        os << "\n";
    }
    return os;
}

template<class number>
QString& operator<<(QString& s, TSquareMatrix<number>& c)
{
    int n = c.row;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            s << c.mtx[i][j];
        }
    }
    return s;
}

template<class number>
TSquareMatrix<number> TSquareMatrix<number>::triangle_matrix() {
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

template<class number>
number TSquareMatrix<number>::det() {
    TSquareMatrix a = this->triangle_matrix();
    number det = a.mtx[0][0];
    for (int i = 1; i < a.row; i++) {
        if (a.mtx[i][i] == number(0))
            return number(0);
        det = det * a.mtx[i][i];
    }
    return det;
}

template<class number>
int TSquareMatrix<number>::rank() {
    TSquareMatrix a = this->triangle_matrix();
    for (int i = this->row - 1; i >= 0; i--) {
        for (int j = 0; j < this->row; j++) {
            if (a.mtx[i][j] != number(0))
                return i + 1;
        }
    }
    return 0;
}


#endif // TSQUARE_MATRIX_H
