#ifndef TRATIONAL_H
#define TRATIONAL_H

#include <iostream>
#include <QString>

class TRational
{
private:
    static QChar SEPARATOR;
    int numerator;
    int denominator;
public:
    TRational();
    TRational(const int &);
    TRational(const int &, const int &);
    TRational(const TRational &);
    TRational(const QByteArray&);

    TRational operator+(const TRational &);
    TRational operator-(const TRational &);
    TRational operator-();
    TRational operator*(const TRational &);
    TRational operator*(const double &);
    TRational operator*(const int &);
    TRational operator/(const double &);
    TRational operator/(const TRational &);

    TRational operator=(const TRational &);
    bool operator==(const TRational &);
    bool operator!=(const TRational &);

    int getNumerator();
    int getDenominator();
    void reduce();

    friend int getGCD(int a, int b);
    friend double abs(TRational &);
    friend QString &operator<<(QString&, TRational&);
    friend std::istream &operator>>(std::istream &, TRational &);
    friend std::ostream &operator<<(std::ostream &, const TRational &);

    static void setSeparator(QChar);
    friend QByteArray &operator>>(QByteArray &, TRational &);
    operator QString ();
};

#endif // TRATIONAL_H
