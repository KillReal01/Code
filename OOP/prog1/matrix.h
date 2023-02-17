#ifndef MATRIX_H
#define MATRIX_H

#include "number.h"
#include <iostream>

class TMatrix {
public:
  TMatrix();
  TMatrix(int);
  TMatrix(const TMatrix &);
  ~TMatrix();

  void set();
  void transpose();
  int rank();
  number det();
  friend std::ostream &operator<<(std::ostream &, TMatrix &);

private:
  int dim;
  number **mtx;

  void clear();
  number **allocate_memory(int);
  TMatrix triangle_matrix();
};

#endif // MATRIX_H
