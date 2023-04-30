#ifndef TINTERFACE_H
#define TINTERFACE_H

#include <QWidget>
#include <QTcpSocket>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QGridLayout>

class TInterface : public QWidget
{
    Q_OBJECT

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();

private:
    int step = 0; //текущее количество ходов
    int score = 0;
    QTcpSocket *socket;
    QByteArray data;

    QPushButton **buttons;
    QPushButton *button_pressed;
    QLabel *your_score, *enemy_score;

    QGridLayout *gridLayout;

signals:
    void recieved(QByteArray);

public slots:
    void readyToRead();
    void recieve(QByteArray);
    void send();
};

void pressButton(QPushButton *&btn, int money);

#endif // TINTERFACE_H
