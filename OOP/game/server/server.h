#ifndef TSERVER_H
#define TSERVER_H


#include <iostream>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QSignalMapper>
#include "clienthandler.h"

const int count_clients = 2;

class TServer : public QTcpServer
{
    Q_OBJECT
public:
    TServer(QObject *parent = nullptr);

private:
    QTcpSocket *socket;
    //QTcpSocket *socket_read = nullptr, *socket_write = nullptr;
    QVector<QTcpSocket *> client_sockets;
    //QVector<QTcpSocket *> client_read, client_write;
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
    void onReadReady();
    void deleteLater();
};

#endif // TSERVER_H
