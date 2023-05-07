#ifndef TSERVER_H
#define TSERVER_H

#include <iostream>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QSignalMapper>
#include <QThread>

const int count_clients = 2;

class TServer : public QTcpServer
{
    Q_OBJECT
public:
    TServer(QObject *parent = nullptr);

private:
    QThread *thread;
    QTcpSocket *socket;
    QVector<QTcpSocket *> client_sockets;
    QByteArray data;


    QVector<int> score, money;
    QVector<int> generateMoney(int);

signals:
    void recieved(QByteArray);

public slots:
    void recieve(QByteArray);
    void send(int, QByteArray);
    void incomingConnection(qintptr) override;
    void onReadReady();
    void deleteLater();
};

#endif // TSERVER_H
