#ifndef COMMON_H
#define COMMON_H

#include <QString>

enum messages
{
    MONEY = 1, //деньги
    INFO //нажатая кнопка соперника + количество очков соперника + деньги
};

extern const QChar separator;
extern const int count_box;
//extern const int count_clients = 2;

QString &operator<<(QString &, const QString &);
QString &operator<<(QString &s, int &c);
QByteArray &operator>>(QByteArray &arr, int &c);

#endif // COMMON_H
