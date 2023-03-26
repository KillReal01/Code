#ifndef POLINOM_H
#define POLINOM_H

#include "number.h"
#include <iostream>

using namespace std;

enum EPrintMode
{
    EPrintModeClassic,
    EPrintModeCanonic,
};

class TPolinom
{
    EPrintMode printMode;
    number a, b, c;
public:
    TPolinom(number,number,number);
    friend ostream& operator<< (ostream&,TPolinom&);
    number value(number);
    void setPrintMode(EPrintMode);

    friend QString& operator<< (QString&,TPolinom&);
};

#endif // POLINOM_H
