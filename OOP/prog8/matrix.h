#ifndef TMATRIX_H
#define TMATRIX_H

#include <iostream>
#include <QString>

template<class number>
class TMatrix
{
private:
    int col;//columns

protected:
    int row; //rows
    number **mtx;

    number **allocate_memory(int, int);
    void clear();

public:
    TMatrix();
    TMatrix(int, int);
    TMatrix(const TMatrix<number> &);
    TMatrix(int, int, QByteArray &);
    TMatrix(int, int, QVector<QVector<number>> &);
    ~TMatrix();

    void set();
    void transpose();
    int getRow();
    int getCol();

    TMatrix<number> &operator=(TMatrix<number> const &other);
    number *operator[](int ind);

    template<class T>
    friend std::ostream &operator<<(std::ostream &, TMatrix<T> &);

    template<class T>
    friend QString &operator<<(QString &s, TMatrix<T> &c);
};

template<class number>
int TMatrix<number>::getRow()
{
    return this->row;
}

template<class number>
int TMatrix<number>::getCol()
{
    return this->col;
}


template<class number>
number* TMatrix<number>::operator[](int ind)
{
    return this->mtx[ind];
}

template<class number>
TMatrix<number> &TMatrix<number>::operator=(TMatrix<number> const &other)
{
    if (this != &other) {
        this->clear();
        this->row = other.row;
        this->col = other.col;
        this->mtx = this->allocate_memory(this->row, this->col);
        for (int i = 0; i < this->row; i++) {
            for (int j = 0; j < this->col; j++) {
                mtx[i][j] = other.mtx[i][j];
            }
        }
    }
    return *this;
}

template<class number>
TMatrix<number>::TMatrix() : row(0), col(0), mtx(nullptr) {}

template<class number>
TMatrix<number>::TMatrix(int n, int m) {
    this->row = n;
    this->col = m;
    mtx = this->allocate_memory(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            mtx[i][j] = number(i + j);
        }
    }
}

template<class number>
TMatrix<number>::TMatrix(int n, int m, QByteArray& arr) {
    this->row = n;
    this->col = m;
    this->mtx = this->allocate_memory(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            number r;
            arr >> r;
            mtx[i][j] = r;
        }
    }
}

template<class number>
TMatrix<number>::TMatrix(int n, int m, QVector<QVector<number>> & vec) {
    this->row = n;
    this->col = m;
    this->mtx = this->allocate_memory(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            number r;
            mtx[i][j] = vec[i][j];
        }
    }
}

template<class number>
TMatrix<number>::TMatrix(const TMatrix<number>& other) {
    this->row = other.row;
    this->col = other.col;

    this->mtx = this->allocate_memory(this->row, this->col);

    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            this->mtx[i][j] = other.mtx[i][j];
        }
    }
}

template<class number>
number** TMatrix<number>::allocate_memory(int n, int m) {
    number** a;
    a = new number * [n];
    for (int i = 0; i < n; i++) {
        a[i] = new number[m];
    }
    return a;
}

template<class number>
TMatrix<number>::~TMatrix() {
    this->clear();
}

template<class number>
void TMatrix<number>::clear() {
    for (int i = 0; i < this->row; i++) {
        delete[] this->mtx[i];
    }
    delete[] this->mtx;
}

template<class number>
void TMatrix<number>::set() {
    this->clear();

    std::cout << "Enter rows: ";
    std::cin >> this->row;

    std::cout << "Enter cols: ";
    std::cin >> this->col;

    std::cout << "Enter matrix:\n";

    mtx = this->allocate_memory(this->row, this->col);
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            std::cin >> mtx[i][j];
        }
    }
}

template<class number>
void TMatrix<number>::transpose() {
    number** tmp = this->allocate_memory(this->col, this->row);
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            tmp[j][i] = this->mtx[i][j];
        }
    }
    this->clear();
    this->mtx = tmp;
    std::swap(this->row, this->col);
}

template<class number>
std::ostream& operator<<(std::ostream& os, TMatrix<number>& a) {
    for (int i = 0; i < a.row; i++) {
        for (int j = 0; j < a.col; j++) {
            os << a.mtx[i][j] << " ";
        }
        os << "\n";
    }
    return os;
}

template<class number>
QString& operator<<(QString& s, TMatrix<number>& c)
{
    int n = c.row;
    int m = c.col;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            s << c.mtx[i][j];
        }
    }
    return s;
}


#endif // TMATRIX_H


