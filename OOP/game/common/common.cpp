#include "common.h"

const QChar separator(';');
const int count_box = 15;

QString& operator<< (QString& m, const QString& s)
{
    m += s + separator;
    return m;
}

QString &operator<<(QString &s, int &c)
{
    s += QString::number(c) + separator;
    return s;
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
