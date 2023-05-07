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

    //отправляем серверу флаг первого подключения
    int rqst = CONNECT;
    QString msg;
    msg << rqst;

    socket->write(msg.toUtf8());
    client_access = UNLOCK;

    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadReady()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));

    //виджеты
    wtext = new QWidget(this);
    wtext->setGeometry(0, 0, this->width(), 100);
    wbuttons = new QWidget(this);
    wbuttons->setGeometry(0, 50, this->width(), this->height());

    //выравнивание кнопок
    gridLayout = new QGridLayout(wbuttons);

    //кнопки
    buttons = new QPushButton *[count_box];
    for (int i = 0; i < count_box; i++) {
        buttons[i] = new QPushButton(QString::number(i + 1), wbuttons);
        gridLayout->addWidget(buttons[i], round(i / 5), i % 5);
        connect(buttons[i], SIGNAL(clicked()), this, SLOT(send()));
    }
    button_exit = new QPushButton("Отключиться", wbuttons);
    connect(button_exit, SIGNAL(clicked()), this, SLOT(exit()));
    gridLayout->addWidget(button_exit, round(count_box / 5) + 1, 4);

    //выравнивание меток
    gridLayoutLabel = new QGridLayout(wtext);

    //метки
    your_score = new QLabel("У вас 0 очков", wtext);
    your_score->setStyleSheet("font-size: 15px;");
    your_score->setAlignment(Qt::AlignCenter);

    turn = new QLabel("Ожидание подключения игрока...", wtext);
    turn->setStyleSheet("font-size: 15px; color: red;");
    turn->setAlignment(Qt::AlignCenter);

    gridLayoutLabel->addWidget(your_score, 0, 0);
    gridLayoutLabel->addWidget(turn, 0, 1);

    //сигнал-слоты
    connect(this,SIGNAL(recieved(QByteArray)),this, SLOT(recieve(QByteArray)));
}

TInterface::~TInterface()
{
    delete wtext;
    delete wbuttons;

    delete your_score;
    delete turn;

    for (int i = 0; i < count_box; i++) {
        delete buttons[i];
    }

    delete[] buttons;
    delete gridLayout;
    delete gridLayoutLabel;
}

void TInterface::exit()
{
    this->close();
}

void TInterface::onReadReady()
{
    if (socket->bytesAvailable()) {
        QByteArray data = socket->readAll();
        qDebug() << "Received data: " << data;
        emit recieved(data);
    }
}

void TInterface::recieve(QByteArray msg) //клиент читает = флаг access + флаг messages + ...
{
    int client_mode = 0;
    msg >> client_access;

    int button_block, enemy_sc, money;
    if (client_access != END) {
        msg >> client_mode;
        switch (client_mode) {
        case INFO: {
            msg >> button_block >> enemy_sc >> money;

            for (int i = 0; i < count_box; i++) {
                if (buttons[i]->text() == QString::number(button_block)) {
                    pressButton(buttons[i], money, false);
                }
            }
            break;
        }
        case MONEY: {
            msg >> money;
            pressButton(button_pressed, money, true);
            score += money;
            your_score->setText("У вас " + QString::number(score) + " очков");
            break;
        }
        }
    }
    if (client_access == END) {
        int enemy_score;
        msg >> enemy_score;
        if (score > enemy_score) {
            QMessageBox::information(this, "Результат игры", "Поздравляем! Вы выиграли!\nСоперник набрал " + QString::number(enemy_score) + " очков");
        } else if (score < enemy_score) {
            QMessageBox::information(this, "Результат игры", "Увы, но Вы проиграли!\nСоперник набрал " + QString::number(enemy_score) + " очков");
        } else {
            QMessageBox::information(this, "Результат игры", "Спорный момент - ничья!\nСоперник набрал " + QString::number(enemy_score) + " очков");
        }
        this->close();
    }

    switch (client_access) {
    case UNLOCK:
        if (step < 5) {
            turn->setStyleSheet("font-size: 15px;color: green;");
            turn->setText("Ваш ход");
        }
        break;
    case LOCK:
        if (step < 5) {
            turn->setStyleSheet("font-size: 15px;color: red;");
            turn->setText("Ход соперника");
        }
        break;
    }
    if (step == 5 && !gameover) {
        turn->setStyleSheet("font-size: 15px;color: red;");
        turn->setText("Ваши ходы закончились");
        QString s;
        int rqst = DISCONNECT;
        s << rqst << score;
        socket->write(s.toUtf8());
        gameover = true;
    }
}

void TInterface::send() //клиент отправляет = флаг request + нажатую кнопку + свои очки
{
    if (step < 5 && client_access == UNLOCK) //если остались ходы и есть доступ, отправляем серверу
    {
        button_pressed = (QPushButton *) sender();
        int btnnum = button_pressed->text().toInt();

        //отправляем серверу флаг не первого подключения
        QString s;
        int rqst = HANDLE;
        s << rqst << btnnum << score;
        socket->write(s.toUtf8());
        step++;
    }
}

void pressButton(QPushButton *&btn, int money, bool flag)
{
    if (flag) {
        btn->setText(QString::number(money) + " $");
    }
    else{
        btn->setText("Открыт");
    }
    btn->setEnabled(false);
    btn->setStyleSheet("color: black;background-color: #c2755d;");
}



