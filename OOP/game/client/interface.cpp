#include "interface.h"
#include "common.h"

TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Игра");
    setFixedSize(600, 400);

    //сокеты
    QString host = "127.0.0.1";
    int port = 2323;

    socket = new QTcpSocket(this);
    socket->connectToHost(host, port);

    //
    socket_write = new QTcpSocket();
    socket_read = new QTcpSocket();
    socket_write->setSocketDescriptor(socket->socketDescriptor());
    socket_read->setSocketDescriptor(socket->socketDescriptor());

    connect(socket_read, SIGNAL(readyRead()), this, SLOT(onReadReady()));
    connect(socket_write, SIGNAL(bytesWritten(qint64)), this, SLOT(onBytesWritten(qint64)));
    //connect(socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));

    //

    //connect(socket, SIGNAL(readyRead()), this, SLOT(onReadReady()));
    //connect(socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));


    //выравнивание кнопок
    gridLayout = new QGridLayout(this);

    //кнопки
    buttons = new QPushButton *[count_box];
    for (int i = 0; i < count_box; i++) {
        buttons[i] = new QPushButton(QString::number(i + 1), this);
        gridLayout->addWidget(buttons[i], round(i / 5), i % 5);
        connect(buttons[i], SIGNAL(clicked()), this, SLOT(send()));
    }

    //метки
    your_score = new QLabel("У вас 0 очков", this);
    enemy_score = new QLabel("У соперника: 0 очков", this);

    your_score->setGeometry(50, 20, 100, 30);
    enemy_score->setGeometry(300, 20, 200, 30);

    //сигнал-слоты
    connect(this,SIGNAL(recieved(QByteArray)),this, SLOT(recieve(QByteArray)));
}

TInterface::~TInterface()
{
    delete your_score;
    delete enemy_score;

    for (int i = 0; i < count_box; i++) {
        delete buttons[i];
    }

    delete[] buttons;
    delete gridLayout;
}

//void TInterface::deleteLater()
//{
//    socket->deleteLater();
//    QString host = "127.0.0.1";
//    int port = 2323;
//    qDebug() << "Disconnected";
//}

void TInterface::onBytesWritten(qint64 bytes)
{
    qDebug() << "Bytes written: " << bytes;
}

void TInterface::onReadReady()
{
    if (socket_read->bytesAvailable()) {
        QByteArray data = socket_read->readAll();
        qDebug() << "Received data: " << data;
        emit recieved(data);
    }
//    if (socket->bytesAvailable()) {
//        QByteArray data = socket->readAll();
//        qDebug() << "Received data: " << data;
//        emit recieved(data);
//    }
}

void TInterface::recieve(QByteArray msg)
{
    int mode;
    msg >> mode;

    switch (mode) {
    case INFO: {
        int button_block, enemy_sc, money;
        msg >> button_block >> enemy_sc >> money;

        for (int i = 0; i < count_box; i++) {
            if (buttons[i]->text() == QString::number(button_block)) {
                pressButton(buttons[i], money);
            }
        }
        enemy_score->setText("У соперника: " + QString::number(enemy_sc) + " очков");
        //socket_write->blockSignals(false);//разблокировать ввод
        break;
    }
    case MONEY: {
        int money;
        msg >> money;

        pressButton(button_pressed, money);
        score += money;
        your_score->setText("У вас " + QString::number(score) + " очков");
        //socket_write->blockSignals(true);//заблокировать ввод
        break;
    }
    }
//    if (step == 5) {
//        QMessageBox msgBox;
//        msgBox.setWindowTitle("Результат игры");

//        if (score < enemy_score->text().toInt())
//            msgBox.setText("Вы проиграли!");
//        else if (score > enemy_score->text().toInt())
//            msgBox.setText("Вы выиграли!");
//        else
//            msgBox.setText("Ничья!");

//        msgBox.exec();
//    }
}

void TInterface::send()
{
    if (step < 5) {
        button_pressed = (QPushButton *) sender();
        int btnnum = button_pressed->text().toInt();

        QString s;
        s << btnnum << score;
        socket_write->write(s.toUtf8());
        step++;
    }
}

void pressButton(QPushButton *&btn, int money)
{
    btn->setText(QString::number(money) + " $");
    btn->setEnabled(false);
    btn->setStyleSheet("color: black;background-color: #FFFF00;");
}



