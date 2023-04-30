#ifndef TSERVER_H
#define TSERVER_H

#include <iostream>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QSignalMapper>

const int count_clients = 2;

class TServer : public QTcpServer
{
    Q_OBJECT
public:
    TServer(QObject *parent = nullptr);

private:
    QTcpSocket *socket;
    QVector<QTcpSocket *> client_sockets;
    QByteArray data;


    QVector<int> score;
    QVector<int> generateMoney(int);

    //QSignalMapper *signalMapper[count_clients];

signals:
    void recieved(QByteArray);


public slots:
    void recieve(QByteArray);
    void send(QByteArray);
    void incomingConnection(qintptr) override;
    void readyToRead();
    void deleteLater();
};

#endif // TSERVER_H
