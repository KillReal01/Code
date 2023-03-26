#include "interface.h"
#include "common.h"

TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Работа №4");
    setFixedSize(300,250);

    name_a = new QLabel("a =",this);
    name_a->setGeometry(50,20,30,25);
    a_re = new QLineEdit("1",this);
    a_re->setGeometry(90,20,50,25);
    delimeter_a = new QLabel("+i",this);
    delimeter_a->setGeometry(150,20,30,25);
    a_im = new QLineEdit("0",this);
    a_im->setGeometry(190,20,50,25);

    name_b = new QLabel("b =",this);
    name_b->setGeometry(50,50,30,25);
    b_re = new QLineEdit("1",this);
    b_re->setGeometry(90,50,50,25);
    delimeter_b = new QLabel("+i",this);
    delimeter_b->setGeometry(150,50,30,25);
    b_im = new QLineEdit("0",this);
    b_im->setGeometry(190,50,50,25);

    name_c = new QLabel("c =",this);
    name_c->setGeometry(50,80,30,25);
    c_re = new QLineEdit("1",this);
    c_re->setGeometry(90,80,50,25);
    delimeter_c = new QLabel("+i",this);
    delimeter_c->setGeometry(150,80,30,25);
    c_im = new QLineEdit("0",this);
    c_im->setGeometry(190,80,50,25);

    name_x = new QLabel("x =",this);
    name_x->setGeometry(50,110,30,25);
    x_re = new QLineEdit("1",this);
    x_re->setGeometry(90,110,50,25);
    delimeter_x = new QLabel("+i",this);
    delimeter_x->setGeometry(150,110,30,25);
    x_im = new QLineEdit("0",this);
    x_im->setGeometry(190,110,50,25);

    value_btn = new QPushButton("знач.",this);
    value_btn->setGeometry(10,150,60,30);
    root_btn = new QPushButton("корни",this);
    root_btn->setGeometry(80,150,60,30);
    print_classic_btn = new QPushButton("класс.",this);
    print_classic_btn->setGeometry(160,150,60,30);
    print_canonic_btn = new QPushButton("канон.",this);
    print_canonic_btn->setGeometry(230,150,60,30);

    output = new QLabel(this);
    output->setGeometry(10,200,280,25);

    connect(value_btn,SIGNAL(pressed()),
            this,SLOT(formRequest()));
    connect(print_classic_btn,SIGNAL(pressed()),
            this,SLOT(formRequest()));
}

TInterface::~TInterface()
{
    delete a_re;
    delete a_im;
    delete name_a;
    delete delimeter_a;

    delete b_re;
    delete b_im;
    delete name_b;
    delete delimeter_b;

    delete c_re;
    delete c_im;
    delete name_c;
    delete delimeter_c;

    delete x_re;
    delete x_im;
    delete name_x;
    delete delimeter_x;

    delete value_btn;
    delete root_btn;
    delete print_classic_btn;
    delete print_canonic_btn;

    delete output;
}

void TInterface::formRequest()
{
    QString msg;
    msg << a_re->text() << a_im->text();
    msg << b_re->text() << b_im->text();
    msg << c_re->text() << c_im->text();
    QPushButton *btn = (QPushButton*)sender();
    if (btn == value_btn)
    {
        msg << QString().setNum(VALUE_REQUEST);
        msg << x_re->text() << x_im->text();
    }
    if (btn == print_classic_btn)
        msg << QString().setNum(PRINT_CLASSIC_REQUEST);
    emit request(msg);
}

void TInterface::answer(QString msg)
{
    QString text;
    int p = msg.indexOf(separator);
    int t = msg.left(p).toInt();
    msg = msg.mid(p+1,msg.length()-p-2);
    switch (t)
    {
        case VALUE_ANSWER:
            text = "p";
            p = msg.indexOf(separator);
            text += msg.left(p);
            text += " = ";
            text += msg.right(msg.length()-p-1);
            output->setText(text);
            break;
        case PRINT_ANSWER:
            text = "p(x) = ";
            text += msg;
            output->setText(text);
            break;
        default: break;
    }
}
