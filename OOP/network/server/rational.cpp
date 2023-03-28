#include "rational.h"
#include "common.h"

QChar TRational::SEPARATOR = separator;

TRational::TRational() {}

TRational::TRational(const int &a)
{
    this->numerator = a;
    this->denominator = 1;
    this->reduce();
}

TRational::TRational(const int &a, const int &b)
{
    this->numerator = a;
    this->denominator = b;
    this->reduce();
}

TRational::TRational(const TRational &other) { // конструктор копирования
    this->numerator = other.numerator;
    this->denominator = other.denominator;
}

TRational TRational::operator+(const TRational &c)
{
    TRational temp;
    temp.numerator = this->numerator * c.denominator + this->denominator * c.numerator;
    temp.denominator = this->denominator * c.denominator;
    temp.reduce();
    return temp;
}

TRational TRational::operator-(const TRational &c)
{
    TRational temp;
    temp.numerator = this->numerator * c.denominator - this->denominator * c.numerator;
    temp.denominator = this->denominator * c.denominator;
    temp.reduce();
    return temp;
}

TRational TRational::operator-()
{
    return TRational(-this->numerator, this->denominator);
}

TRational TRational::operator*(const TRational &c)
{
    TRational temp(c.numerator * this->numerator, c.denominator * this->denominator);
    temp.reduce();
    return temp;
}

TRational TRational::operator*(const int &n)
{
    TRational temp (n * this->numerator, this->denominator);
    temp.reduce();
    return temp;
}


TRational TRational::operator/(const TRational &c)
{
    TRational temp(c.denominator * this->numerator, c.numerator * this->denominator);
    temp.reduce();
    return temp;
}

TRational TRational::operator=(const TRational &c)
{
    this->numerator = c.numerator;
    this->denominator = c.denominator;
    return *this;
}

int getGCD(int a, int b)
{
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void TRational::reduce()
{
    int del = getGCD(this->numerator, this->denominator);
    this->numerator /= del;
    this->denominator /= del;
}

bool TRational::operator==(const TRational &c)
{
    return (this->numerator == c.numerator && this->denominator == c.denominator);
}

bool TRational::operator!=(const TRational &c)
{
    return !(this->numerator == c.numerator && this->denominator == c.denominator);
}

double abs(TRational &c)
{
    if (c.numerator < 0)
        return double(-c.numerator) / double(c.denominator);
    else
        return double(c.numerator) / double(c.denominator);
}

std::istream &operator>>(std::istream &is, TRational &c)
{
    is >> c.numerator >> c.denominator;
    return is;
}

std::ostream &operator<<(std::ostream &os, const TRational &c)
{
    os << c.numerator << "/" << c.denominator;
    return os;
}

QString &operator<<(QString &s, TRational &c)
{
    s += QString::number(c.getNumerator()) + TRational::SEPARATOR;
    s += QString::number(c.getDenominator()) + TRational::SEPARATOR;
    return s;
}

int TRational::getNumerator()
{
    return this->numerator;
}

int TRational::getDenominator(){
    return this->denominator;
}

TRational::TRational(const QByteArray& arr)
{
    int p = arr.indexOf(TRational::SEPARATOR.toLatin1());
    this->numerator = arr.left(p).toInt();

    p = arr.indexOf(TRational::SEPARATOR.toLatin1());
    this->denominator = arr.right(arr.length() - p - 1).toInt();
}

QByteArray& operator>>(QByteArray& arr, TRational& c)
{
    int p = arr.indexOf(TRational::SEPARATOR.toLatin1());
    p = arr.indexOf(TRational::SEPARATOR.toLatin1(), p + 1);
    if (p > 0)
    {
        c = TRational(arr.left(p));
        arr = arr.right(arr.length() - p - 1);
    }
    return arr;
}

void TRational::setSeparator(QChar ch)
{
    SEPARATOR = ch;
}
