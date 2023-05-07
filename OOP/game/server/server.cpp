#include "server.h"
#include "common.h"

TServer::TServer(QObject *parent)
    : QTcpServer(parent), thread(nullptr)
{
    if (this->listen(QHostAddress::Any, 2323)){
        qDebug() << "server started";
        srand(time(NULL));
        money = generateMoney(count_box);
        qDebug() << "generate money:";
        for (int i = 0; i < count_box; i++) {
            std::cout << money[i] << " ";
        }
        qDebug() << "\nwait clients...";
        connect(this, SIGNAL(recieved(QByteArray)), this, SLOT(recieve(QByteArray)));
    }
    else
        qDebug() << "error server";
}

void TServer::incomingConnection(qintptr socketDescriptor)
{
    if (client_sockets.size() < count_clients)
    {
        socket = new QTcpSocket();
        socket->setSocketDescriptor(socketDescriptor);
        connect(socket, SIGNAL(readyRead()), this, SLOT(onReadReady()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
        client_sockets.push_back(socket);
        qDebug() << "client connected " << socketDescriptor;
    }
    else
    {
        qDebug() << "server loaded!";
    }
}


void TServer::deleteLater()
{
    for (int i = 0; i < client_sockets.size(); i++) {
        client_sockets[i]->deleteLater();
    }
    client_sockets.clear();
    money = generateMoney(count_box);
    //другим написать конец игры
}

void TServer::onReadReady()
{
    socket = (QTcpSocket *) sender();
    if (socket->bytesAvailable()) {
        QByteArray data = socket->readAll();
        qDebug() << "recieved" << data << "from" << socket->socketDescriptor();
        emit recieved(data);
    }
}

void TServer::recieve(QByteArray arr)
{
    QString answer;
    int rqst;
    arr >> rqst;

    switch (rqst) {
    case CONNECT: { //клиент подключился 1 раз
        int acs = LOCK;
        answer << acs;

        socket->write(answer.toUtf8());
        if (client_sockets.size() == count_clients) {
            //разрешаем передачу данных первому подключившимуся и запрещаем остальным
            qDebug() << "can play game";
            acs = UNLOCK;
            answer = "";
            answer << acs;
            client_sockets[0]->write(answer.toUtf8());
            qDebug() << "sended" << answer << "to" << client_sockets[0]->socketDescriptor();
        }
        break;
    }

    case HANDLE:{ //клиент подключился не 1 раз, запрещаем ему отправлять данные
        //Ответ = нажатая кнопка соперника + количество очков соперника + деньги
        int button_clicked, sc;
        arr >> button_clicked >> sc;

        answer << button_clicked;
        sc += money[button_clicked - 1];
        answer << sc;

        answer << money[button_clicked - 1];
        qDebug() << socket->socketDescriptor() << "handle";

        send(LOCK, answer.toUtf8());
        break;
    }
    case DISCONNECT: { //клиент отправляет запрос на отключение
        qDebug() << "disconnect";
        int sc;
        arr >> sc;
        score.append(sc);
        if (score.size() == count_clients) {
            int acs = END;
            answer = "";
            answer << acs << score[1];
            client_sockets[0]->write(answer.toUtf8());

            answer = "";
            answer << acs << score[0];
            client_sockets[1]->write(answer.toUtf8());
            score.clear();
        }
        break;
    }
    }
}

void TServer::send(int connect, QByteArray arr)
{
    //доступ + режим + данные
    QString answer;
    int mode, button_clicked, sc, money;
    arr >> button_clicked >> sc >> money;

    for (int i = 0; i < client_sockets.size(); i++) {
        answer = "";
        if (client_sockets[i] != socket) { //отправить другим клиентам
            int acs = UNLOCK;
            mode = INFO;
            answer << acs << mode << button_clicked << sc << money;
            client_sockets[i]->write(answer.toUtf8());
            qDebug() << "sended" << answer << "to" << client_sockets[i]->socketDescriptor();
        } else { //отправить клиенту, от которого получили сообщение
            int acs = LOCK;
            mode = MONEY;
            answer << acs << mode << money;
            socket->write(answer.toUtf8());
            qDebug() << "sended" << answer << "to" << socket->socketDescriptor();
        }
    }
}

QVector<int> TServer::generateMoney(int n)
{
    QVector<int> money(n);
    for (int i = 0; i < n; i++) {
        money[i] = rand() % 10;
    }
    return money;
}


