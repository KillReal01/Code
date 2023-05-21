#include "matrix.h"

TMatrix::TMatrix() { }

TMatrix::TMatrix(int n, int m) {
    this->row = n;
    this->col = m;
    mtx = this->allocate_memory(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            mtx[i][j] = number(i + j);
        }
    }
}

TMatrix::TMatrix(int n, int m, QByteArray& arr) {
    this->row = n;
    this->col = m;
    mtx = this->allocate_memory(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            number r;
            arr >> r;
            mtx[i][j] = r;
        }
    }
}

TMatrix::TMatrix(const TMatrix& other) { 
    this->row = other.row;
    this->col = other.col;
    
    this->mtx = this->allocate_memory(this->row, this->col);

    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            this->mtx[i][j] = other.mtx[i][j];
        }
    }
}

number** TMatrix::allocate_memory(int n, int m) {
    number** a;
    a = new number * [n];
    for (int i = 0; i < n; i++) {
        a[i] = new number[m];
    }
    return a;
}

TMatrix::~TMatrix() {
    this->clear();
}

void TMatrix::clear() {
    for (int i = 0; i < this->row; i++) {
        delete[] this->mtx[i];
    }
    delete[] this->mtx;
}


void TMatrix::set() {
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

void TMatrix::transpose() {
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

std::ostream& operator<<(std::ostream& os, TMatrix& a) {
    for (int i = 0; i < a.row; i++) {
        for (int j = 0; j < a.col; j++) {
            os << a.mtx[i][j] << " ";
        }
        os << "\n";
    }
    return os;
}

QString& operator<<(QString& s, TMatrix& c)
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
