#ifndef MATRIX_H
#define MATRIX_H

#include "number.h"
#include <iostream>

class TMatrix {
public:
  TMatrix();
  TMatrix(int);
  TMatrix(TMatrix *);
  ~TMatrix();

  void set();
  void transpose();
  int rank();
  number det();

  friend std::ostream &operator<<(std::ostream &, TMatrix &);
  // void print();
  // TMatrix operator*(const int);
  // TMatrix &operator=(const TMatrix &);

private:
  int dim = 5;
  number **mtx;

  void clear();
  number **allocate_memory(int);
  TMatrix triangle_matrix();
};

#endif // MATRIX_H
