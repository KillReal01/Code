#include "server.h"
#include "common.h"

TServer::TServer(QObject *parent)
    : QTcpServer(parent)
{
    if (this->listen(QHostAddress::Any, 2323)){
        qDebug() << "server started";
        srand(time(NULL));
        score = generateMoney(count_box);
        qDebug() << "money:";
        for (int i = 0; i < count_box; i++) {
            std::cout << score[i] << " ";
        }
        qDebug() << "\nwait clients...";
    }
    else
        qDebug() << "error server";
}

void TServer::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket();
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyToRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
    connect(this, SIGNAL(recieved(QByteArray)), this, SLOT(recieve(QByteArray)));


//    // Connect signals to slots using loop
//    for (int i = 0; i < count_clients; i++) {
//        signalMapper[i] = new QSignalMapper(this); // create signal mapper object
//        connect(signalMapper[i], SIGNAL(mapped(int)), this, SLOT(onSignal(int))); // connect signal to slot
//        signalMapper[i]->setMapping(buttons[i], i); // map signal to data
//        connect(buttons[i], SIGNAL(clicked()), signalMapper[i], SLOT(map())); // connect button to signal mapper
//    }

    //connect(socket, SIGNAL(connected()), this, SLOT(onSokConnected()));

    client_sockets.push_back(socket);

    qDebug() << "client connected " << socketDescriptor;
}


void TServer::deleteLater()
{
    //QTcpSocket *delsocket = (QTcpSocket *) sender();
    for (int i = 0; i < client_sockets.size(); i++) {
        client_sockets[i]->deleteLater();
    }
    client_sockets.clear();
    //другим написать конец игры
}

void TServer::readyToRead()
{
    socket = (QTcpSocket *) sender();
    if (socket->bytesAvailable()) {
        QByteArray data = socket->readAll();
        qDebug() << "server recieved from" << socket->socketDescriptor() << data;
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
            qDebug() << "server sended money" << answer <<  "to" << socket->socketDescriptor();
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





