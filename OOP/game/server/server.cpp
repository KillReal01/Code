#include "server.h"
#include "common.h"

TServer::TServer(QObject *parent)
    : QTcpServer(parent)
{
    if (this->listen(QHostAddress::Any, 2323)){
        qDebug() << "server started";
        srand(time(NULL));
        score = generateMoney(count_box);
        qDebug() << "generate money:";
        for (int i = 0; i < count_box; i++) {
            std::cout << score[i] << " ";
        }
        qDebug() << "\nwait clients...";
        connect(this, SIGNAL(recieved(QByteArray)), this, SLOT(recieve(QByteArray)));
    }
    else
        qDebug() << "error server";
}

void TServer::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket();
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket,SIGNAL(readyRead()), this, SLOT(onReadReady()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
    client_sockets.push_back(socket);

    qDebug() << "client connected " << socketDescriptor;
}


void TServer::deleteLater()
{
    for (int i = 0; i < client_sockets.size(); i++) {
        client_sockets[i]->deleteLater();
    }
    client_sockets.clear();
    score = generateMoney(count_box);
    //другим написать конец игры
}

void TServer::onReadReady()
{
    socket = (QTcpSocket *) sender();
    if (socket->bytesAvailable()) {
        QByteArray data = socket->readAll();
        qDebug() << "recieved from" << socket->socketDescriptor() << data;
        emit recieved(data);
    }
}

void TServer::recieve(QByteArray arr)
{
    //Ответ = нажатая кнопка соперника + количество очков соперника + деньги
    QString answer;

    int button_clicked, sc;
    arr >> button_clicked >> sc;

    answer << button_clicked;
    sc += score[button_clicked - 1];
    answer << sc;

    answer << score[button_clicked - 1];
    send(answer.toUtf8());
}

void TServer::send(QByteArray arr)
{
    //режим + данные
    QString answer;
    int mode, button_clicked, sc, money;
    arr >> button_clicked >> sc >> money;

    for (int i = 0; i < client_sockets.size(); i++) {
        if (client_sockets[i] != socket){//отправить другим клиентам
            answer = "";
            mode = INFO;
            answer << mode << button_clicked << sc << money;
            client_sockets[i]->write(answer.toUtf8());
            qDebug() << "sended" << answer << "to" << client_sockets[i]->socketDescriptor();
        }
        else{//отправить клиенту, от которого получили сообщение
            answer = "";
            mode = MONEY;
            answer << mode << money;
            socket->write(answer.toUtf8());
            qDebug() << "sended" << answer <<  "to" << socket->socketDescriptor();
        }
    }
}

QVector<int> TServer::generateMoney(int n)
{
    QVector<int> score(n);
    for (int i = 0; i < n; i++) {
        score[i] = rand() % 10 * 10;
    }
    return score;
}





