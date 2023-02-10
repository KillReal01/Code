#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include "matrix.h"
#include "number.h"


class TApplication
{
public:
    TApplication();
    int exec();
private:
    int menu();
};

#endif // APPLICATION_H
