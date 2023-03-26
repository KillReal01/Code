#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
using namespace std;

#include <QString>

class complex
{
    static QChar SEPARATOR;

    double re,im;
public:
    complex();
    complex(const int&);
    complex(double,double);
    complex(const QByteArray&);

    complex operator+ (complex);
    complex operator* (complex);
    bool operator==(complex);

    static void setSeparator(QChar);

    friend ostream& operator<<(ostream&,complex);
    friend istream& operator>>(istream&,complex&);

    friend QString& operator<<(QString&,complex);
    friend QByteArray& operator>>(QByteArray&,complex&);
    operator QString ();
};

#endif // COMPLEX_H
