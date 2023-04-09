#ifndef TSQUARE_MATRIX_H
#define TSQUARE_MATRIX_H

#include <iostream>
#include "matrix.h"

class TSquareMatrix : public TMatrix {
public:
    TSquareMatrix();
    TSquareMatrix(int);
    TSquareMatrix(const TSquareMatrix &);
    TSquareMatrix(int, QByteArray &);

    //деструктор вызовется в родителе

    number det();
    int rank();
    void transpose() override;
    void set() override;

    friend std::ostream &operator<<(std::ostream &, TSquareMatrix &);
    friend QString &operator<<(QString &s, TSquareMatrix &c);

private:
	TSquareMatrix triangle_matrix();
};

#endif // TSQUARE_MATRIX_H
