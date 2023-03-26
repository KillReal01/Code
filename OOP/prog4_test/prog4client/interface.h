#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class TInterface : public QWidget
{
    Q_OBJECT

    QLabel *name_a, *delimeter_a;
    QLineEdit *a_re, *a_im;
    QLabel *name_b, *delimeter_b;
    QLineEdit *b_re, *b_im;
    QLabel *name_c, *delimeter_c;
    QLineEdit *c_re, *c_im;
    QLabel *name_x, *delimeter_x;
    QLineEdit *x_re, *x_im;

    QPushButton *value_btn;
    QPushButton *root_btn;
    QPushButton *print_classic_btn;
    QPushButton *print_canonic_btn;

    QLabel *output;

//    friend QString& operator<< (QString&,const QString&);

public:
    TInterface(QWidget *parent = 0);
    ~TInterface();

public slots:
    void answer(QString);

private slots:
    void formRequest();

signals:
    void request(QString);

};

#endif // INTERFACE_H
