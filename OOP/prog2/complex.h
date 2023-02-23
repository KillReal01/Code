#ifndef TCOMPLEX_H
#define TCOMPLEX_H

#include <iostream>

class TComplex
{
private:
    double real, image;

public:
    TComplex();
    TComplex(const double &);
    TComplex(const double &, const double &);

    TComplex operator+(const TComplex &);
    TComplex operator-(const TComplex &);
    TComplex operator-();
    TComplex operator*(const TComplex &);
    TComplex operator*(const double &);
    TComplex operator*(const int &);
    TComplex operator/(const double &);
    TComplex operator/(const TComplex &);

    TComplex operator=(const TComplex &);
    bool operator==(const TComplex &);
    bool operator!=(const TComplex &);

    double getReal();
    double getImage();
    friend double abs(TComplex&);

    friend std::istream& operator >> (std::istream &, TComplex&);
    friend std::ostream& operator << (std::ostream &, const TComplex&);
};

#endif // TCOMPLEX_H
