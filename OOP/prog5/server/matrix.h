#ifndef TMATRIX_H
#define TMATRIX_H

#include <iostream>
#include "number.h"

class TMatrix{
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
    TMatrix(const TMatrix &);
    TMatrix(int, int, QByteArray &);
    ~TMatrix();

    virtual void set();
    virtual void transpose();

    friend std::ostream &operator<<(std::ostream &, TMatrix &);
    friend QString &operator<<(QString &s, TMatrix &c);
};

#endif // TMATRIX_H


