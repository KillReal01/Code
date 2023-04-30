#include "common.h"

const QChar separator(';');

QString& operator<< (QString& m, const QString& s)
{
    m += s;
    m.append(separator);
    return m;
}

QByteArray &operator>>(QByteArray &arr, double &c)
{
    QString s;
    int p = arr.indexOf(separator.toLatin1());
    if (p > 0) {
        s = QString(arr.left(p));
        c = s.toDouble();
        arr = arr.right(arr.length() - p - 1);
    }
    return arr;
}

QByteArray &operator>>(QByteArray &arr, int &c)
{
    QString s;
    int p = arr.indexOf(separator.toLatin1());
    if (p > 0) {
        s = QString(arr.left(p));
        c = s.toInt();
        arr = arr.right(arr.length() - p - 1);
    }
    return arr;
}

QString &operator<<(QString &s, double &c)
{
    s += QString::number(c) + separator;
    return s;
}

QString &operator<<(QString &s, int &c)
{
    s += QString::number(c) + separator;
    return s;
}
