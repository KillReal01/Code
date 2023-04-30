#ifndef COMMON_H
#define COMMON_H

#include <QString>

enum messages
{
    DETERMINANT = 1,
    RANK,
    TRANSPOSE,
};

enum modes
{
    REAL_MODE = 1,
    COMPLEX_MODE,
    RATIONAL_MODE,
};

extern const QChar separator;

QString& operator<< (QString&,const QString&);
QString &operator<<(QString &s, double &c);
QString &operator<<(QString &s, int &c);

QByteArray &operator>>(QByteArray &arr, double &c);
QByteArray &operator>>(QByteArray &arr, int &c);

#endif // COMMON_H
