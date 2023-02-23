#include "complex.h"

TComplex::TComplex()
{

}

TComplex::TComplex(const double &n)
{
    this->real = n;
    this->image = 0;
}

TComplex::TComplex(const double &a, const double &b)
{
    this->real = a;
    this->image = b;
}

TComplex TComplex::conjugate_number()
{
    TComplex temp;
    temp.real = this->real;
    temp.image = -this->image;
    return temp;
}

TComplex TComplex::operator+(const TComplex &c)
{
    TComplex temp;
    temp.real = this->real + c.real;
    temp.image = this->image + c.image;
    return temp;
}

TComplex TComplex::operator-(const TComplex &c)
{
    TComplex temp;
    temp.real = this->real - c.real;
    temp.image = this->image - c.image;
    return temp;
}

TComplex TComplex::operator-()
{
    TComplex temp;
    temp.real = -this->real;
    temp.image = -this->image;
    return temp;
}

TComplex TComplex::operator*(const TComplex &c)
{
    TComplex temp;
    temp.real = this->real * c.real - this->image * c.image;
    temp.image = this->image * c.real + this->real * c.image;
    return temp;
}

TComplex TComplex::operator*(const double &n)
{
    TComplex temp;
    temp.real = this->real * n;
    temp.image = this->image * n;
    return temp;
}

TComplex TComplex::operator*(const int &n)
{
    TComplex temp;
    temp.real = this->real * n;
    temp.image = this->image * n;
    return temp;
}

TComplex TComplex::operator/(const double &n)
{
    TComplex temp;
    temp.real = this->real / n;
    temp.image = this->image / n;
    return temp;
}

TComplex TComplex::operator/(const TComplex &c)
{
    TComplex res(*this);
    double del = c.real * c.real + c.image * c.image;
    res = res * res.conjugate_number() / del;
    return res;
}

TComplex TComplex::operator=(const TComplex &c)
{
    this->real = c.real;
    this->image = c.image;
    return *this;
}

bool TComplex::operator==(const TComplex &c)
{
    return (this->real == c.real && this->image == c.image);
}

bool TComplex::operator!=(const TComplex &c)
{
    return !(this->real == c.real && this->image == c.image);
}

bool TComplex::operator>(const TComplex &c)
{
    return (this->real > c.real);
}

bool TComplex::operator<(const TComplex &c)
{
    return (this->real < c.real);
}

TComplex abs(const TComplex &c)
{
    TComplex temp;
    temp.real = (c.real > 0) ? c.real : -c.real;
    temp.image = (c.image > 0) ? c.image : -c.image;
    return temp;
}

//TComplex TComplex::abs(const TComplex & c)
//{
//    TComplex temp;
//    temp.real = std::abs(c.real);
//    temp.image = std::abs(c.image);
//    return temp;
//}

//std::iostream &std::abs(std::iostream &s, TComplex &c)
//{
//    TComplex temp;
//    temp.real = std::abs(c.real);
//    temp.image = std::abs(c.image);
//    s << temp;
//    return s;
//}

std::istream& operator>>(std::istream &is, const TComplex& c)
{
    is >> c.real >> c.image;
    return is;
}

std::ostream& operator<<(std::ostream &os, const TComplex& c)
{
    os << "(" << c.real;
    if (c.image >= 0)
        os << "+";
    os << c.image << "i)";
    return os;
}
