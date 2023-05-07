#ifndef COMMON_H
#define COMMON_H

#include <QString>

enum messages
{
    MONEY = 1, //деньги
    INFO, //нажатая кнопка соперника + количество очков соперника + деньги
};

enum access//отправляет сервер, обрабатывает клиент
{
    LOCK = 1,
    UNLOCK,
    END
};

enum request//отправляет клиент, обрабатывает клиент сервер
{
    CONNECT = 1,//первое обращение к серверу
    HANDLE,//не первое обращение к серверу
    DISCONNECT//сделан последний ход
};

extern const QChar separator;
extern const int count_box;

QString &operator<<(QString &, const QString &);
QString &operator<<(QString &s, int &c);
QByteArray &operator>>(QByteArray &arr, int &c);

#endif // COMMON_H
