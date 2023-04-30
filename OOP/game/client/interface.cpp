#include "interface.h"
#include "common.h"

TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Игра");
    setFixedSize(600, 500);

    //сокет
    socket = new QTcpSocket();
    socket->connectToHost("127.0.0.1", 2323);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyToRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));

    //выравнивание кнопок
    gridLayout = new QGridLayout(this);
    this->setLayout(gridLayout);
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

    your_score->setGeometry(50, 25, 100, 50);
    enemy_score->setGeometry(200, 25, 200, 50);

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

void TInterface::readyToRead()
{
    qDebug() << "bytesAvailable " << socket->bytesAvailable();
    if (socket->bytesAvailable()) {
        QByteArray data = socket->readAll();
        qDebug() << "recieved " << data;
        emit recieved(data);
    }
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
        break;
    }
    case MONEY: {
        int money;
        msg >> money;

        pressButton(button_pressed, money);
        score += money;
        your_score->setText("У вас " + QString::number(score) + " очков");
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
        QPushButton *button_send = (QPushButton *) sender();
        button_pressed = button_send;
        //pressButton(button_send);

        int btnnum = button_send->text().toInt();
        QString s;
        s << btnnum;
        s << score;

        socket->write(s.toUtf8());
        step++;
    }
}

void pressButton(QPushButton *&btn, int money)
{
    btn->setText(QString::number(money) + " $");
    btn->setEnabled(false);
    btn->setStyleSheet("color: black;background-color: #FFFF00;");
}



