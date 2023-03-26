#include "complex.h"
#include "common.h"

QChar complex::SEPARATOR = separator;

complex::complex()
{
    re = im = 0;
}

complex::complex(const int& r)
{
    re = r;
    im = 0;
}

complex::complex(double r, double i)
{
    re = r;
    im = i;
}

complex complex::operator+ (complex c)
{
    complex t;
    t.re = re + c.re;
    t.im = c.im + im;
    return t;
}

complex complex::operator* (complex c)
{
    complex t;
    t.re = re*c.re - im*c.im;
    t.im = re*c.im + im*c.re;
    return t;
}

ostream& operator<<(ostream& os,complex c)
{
    os<<"("<<c.re<<"+"<<c.im<<"i)";
    return os;
}

istream& operator>>(istream& is,complex& c)
{
    is>>c.re>>c.im;
    return is;
}

bool complex::operator==(complex c)
{
    return (re==c.re)&&(im==c.im);
}

complex::operator QString ()
{
    QString s = "(";
    s += QString().setNum(re);
    s += "+";
    s += QString().setNum(im);
    s += "i)";
    return s;
}

QString& operator<<(QString& s, complex c)
{
    s += "(";
    s += QString().setNum(c.re);
    s += "+";
    s += QString().setNum(c.im);
    s += "i)";
    return s;
}

complex::complex(const QByteArray& arr)
{
    //int p = arr.indexOf(SEPARATOR);
    int p = arr.indexOf(';');
    re = arr.left(p).toDouble();
    im = arr.right(arr.length()-p-1).toDouble();
}

QByteArray& operator>>(QByteArray& arr, complex& c)
{
    //int p = arr.indexOf(complex::SEPARATOR);
    //p = arr.indexOf(complex::SEPARATOR,p+1);
    int p = arr.indexOf(';');
    p = arr.indexOf(';',p+1);
    if (p > 0)
    {
        c = complex(arr.left(p));
        arr = arr.right(arr.length()-p-1);
    }
    return arr;
}

void complex::setSeparator(QChar ch)
{
    SEPARATOR = ch;
}
