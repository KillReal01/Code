#include "polinom.h"

TPolinom::TPolinom(number x,number y,number z)
{
    printMode = EPrintModeClassic;
    a = x;
    b = y;
    c = z;
}

ostream& operator<< (ostream& os,TPolinom& p)
{
    if (p.printMode == EPrintModeClassic)
        os<<p.a<<"x^2+"<<p.b<<"x+"<<p.c;
    else
    {
        //to do
    }
    return os;
}

number TPolinom::value(number x)
{
    return a*x*x+b*x+c;
}

void TPolinom::setPrintMode(EPrintMode m)
{
    printMode = m;
}

QString& operator<< (QString& s, TPolinom& p)
{
    s<<p.a;
    s += "x^2+";
    s<<p.b;
    s += "x+";
    s<<p.c;
    return s;
}
