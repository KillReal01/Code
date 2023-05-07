#ifndef TINTERFACE_H
#define TINTERFACE_H

#include <QWidget>
#include <QTcpSocket>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QGridLayout>
#include <QThread>
#include <QVBoxLayout>
#include <QMutex>


class TInterface : public QWidget
{
    Q_OBJECT

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();

private:
    int step = 0; //текущее количество ходов
    int score = 0;

    int client_access;

    QWidget *wtext, *wbuttons;

    QTcpSocket *socket;
    QByteArray data;

    QPushButton **buttons;
    QPushButton *button_pressed, *button_exit;
    QLabel *your_score, *turn;

    QGridLayout *gridLayout, *gridLayoutLabel;
    bool gameover = false;

signals:
    void recieved(QByteArray);
    void endGame();

public slots:
    void onReadReady();
    void exit();
    void recieve(QByteArray);
    void send();
};

void pressButton(QPushButton *&btn, int money, bool flag);

#endif // TINTERFACE_H
