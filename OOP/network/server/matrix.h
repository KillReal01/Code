#ifndef MATRIX_H
#define MATRIX_H

//#include <QLineEdit>
#include <iostream>
#include "number.h"

class TMatrix {
public:
  TMatrix();
  TMatrix(int);
  TMatrix(const TMatrix &);
  TMatrix(int, QByteArray &);
  //TMatrix(int, QLineEdit ***, QLineEdit ***);
  ~TMatrix();

  void set();
  void transpose();
  int rank();
  number det();

  //void getMtx(QLineEdit ***&, QLineEdit ***&);
  friend std::ostream &operator<<(std::ostream &, TMatrix &);
  friend QString & operator << (QString &, TMatrix &);

private:
  int dim;
  number **mtx;

  void clear();
  number **allocate_memory(int);
  TMatrix triangle_matrix();
};

#endif // MATRIX_H
