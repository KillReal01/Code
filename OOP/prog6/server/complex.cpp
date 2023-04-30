#include "complex.h"
#include "common.h"
#include <math.h>

QChar TComplex::SEPARATOR = separator;

TComplex::TComplex() {}

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
    TComplex res(*this), temp(c.real, -c.image);
    double del = c.real * c.real + c.image * c.image;
    res = res * temp / del;
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

double abs(TComplex &c)
{
    return std::sqrt(c.getReal() * c.getReal() + c.getImage() * c.getImage());
}

double TComplex::getReal()
{
    return this->real;
}

double TComplex::getImage()
{
    return this->image;
}

std::istream& operator>>(std::istream &is, TComplex& c)
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

QString &operator<<(QString &s, TComplex &c)
{
    s += QString::number(c.getReal()) + TComplex::SEPARATOR;
    s += QString::number(c.getImage()) + TComplex::SEPARATOR;
    return s;
}

TComplex::TComplex(const QByteArray& arr)
{
    int p = arr.indexOf(TComplex::SEPARATOR.toLatin1());
    this->real = arr.left(p).toDouble();

    p = arr.indexOf(TComplex::SEPARATOR.toLatin1());
    this->image = arr.right(arr.length() - p - 1).toDouble();
}

QByteArray& operator>>(QByteArray& arr, TComplex& c)
{
    int p = arr.indexOf(TComplex::SEPARATOR.toLatin1());
    p = arr.indexOf(TComplex::SEPARATOR.toLatin1(), p + 1);
    if (p > 0)
    {
        c = TComplex(arr.left(p));
        arr = arr.right(arr.length() - p - 1);
    }
    return arr;
}

TComplex::operator QString()
{
    QString s;
    s = QString::number(this->real) + "+" + QString::number(this->image) + "i";
    return s;
}

void TComplex::setSeparator(QChar ch)
{
    SEPARATOR = ch;
}
