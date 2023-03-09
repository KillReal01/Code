#include "matrix.h"
#include <math.h>

TMatrix::TMatrix() {} // конструктор

TMatrix::TMatrix(int n) { // конструктор
  this->dim = n;
  mtx = this->allocate_memory(n);
  for (int i = 0; i < this->dim; i++) {
    for (int j = 0; j < this->dim; j++) {
      mtx[i][j] = number(i + j);
    }
  }
}

TMatrix::TMatrix(int n, QLineEdit *** numerator, QLineEdit *** denominator){
  this->dim = n;
  mtx = this->allocate_memory(n);
  for (int i = 0; i < this->dim; i++) {
    for (int j = 0; j < this->dim; j++) {
      mtx[i][j] = number(numerator[i][j]->text().toInt(), denominator[i][j]->text().toInt());
    }
  }
}

TMatrix::~TMatrix() { this->clear(); } // деструктор

TMatrix::TMatrix(const TMatrix &other) { // конструктор копирования
  int d = other.dim;
  this->mtx = this->allocate_memory(d);
  this->dim = d;
  for (int i = 0; i < d; i++) {
    for (int j = 0; j < d; j++) {
      this->mtx[i][j] = other.mtx[i][j];
    }
  }
}

void TMatrix::getMtx(QLineEdit ***&numerator, QLineEdit ***&denominator)
{
  int n = this->dim;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      numerator[i][j]->setText(QString::number(mtx[i][j].getNumerator()));
      denominator[i][j]->setText(QString::number(mtx[i][j].getDenominator()));
    }
  }
}

number **TMatrix::allocate_memory(int n) {
  number **a;
  a = new number *[n];
  for (int i = 0; i < n; i++) {
    a[i] = new number[n];
  }
  return a;
}

void TMatrix::set() { // ввод данных матрицы
  this->clear();

  std::cout << "Enter dimension: ";
  std::cin >> this->dim;
  std::cout << "Enter matrix:\n";

  mtx = this->allocate_memory(this->dim);
  for (int i = 0; i < this->dim; i++) {
    for (int j = 0; j < this->dim; j++) {
      std::cin >> mtx[i][j];
    }
  }
}

void TMatrix::clear() { // освобождение памяти
  for (int i = 0; i < this->dim; i++) {
    delete[] mtx[i];
  }
  delete[] mtx;
}

void TMatrix::transpose() { // транспонирование матрицы
  for (int i = 0; i < this->dim; i++) {
    for (int j = i; j < this->dim; j++) {
      std::swap(this->mtx[i][j], this->mtx[j][i]);
    }
  }
}

TMatrix TMatrix::triangle_matrix() {
  TMatrix a(*this);
  int n = a.dim;

  int countSwaps = 1;
  double eps = 1.0e-6;

  for (int i = 0; i < n; ++i) {
    // находим строку с максимальным первым элементом
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

    //  вычитаем текущую строку из всех остальных
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

  a.mtx[0][0] = a.mtx[0][0] * countSwaps; // надо поменять знак определителя
  return a;
}

number TMatrix::det() { // определитель матрицы
  TMatrix a = this->triangle_matrix();
  number det = a.mtx[0][0];
  for (int i = 1; i < a.dim; i++) {
    if (a.mtx[i][i] == number(0))
      return number(0);
    det = det * a.mtx[i][i];
  }
  return det;
}

int TMatrix::rank() { // ранг матрицы
  TMatrix a = this->triangle_matrix();
  // std::cout << a << "\n";
  for (int i = this->dim - 1; i >= 0; i--) {
    for (int j = 0; j < this->dim; j++) {
      if (a.mtx[i][j] != number(0))
        return i + 1;
    }
  }
  return 0;
}

std::ostream &operator<<(std::ostream &os, TMatrix &a) {
  for (int i = 0; i < a.dim; i++) {
    for (int j = 0; j < a.dim; j++) {
      os << a.mtx[i][j] << " ";
    }
    os << "\n";
  }
  return os;
}
