#include "interface.h"
#include "common.h"

TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Работа №6");
    setFixedSize(700, 550);

    // поля для кнопок
    button_det = new QPushButton("Определитель", this);
    button_rank = new QPushButton("Ранг", this);
    button_transpose = new QPushButton("Транспонировать", this);
    button_enter = new QPushButton("Ввести размер", this);
    button_accept = new QPushButton("Задать размер", this);
    button_accept->setFixedWidth(100);
    button_accept->hide();

    //поля для выбора режима работы
    mode_real = new QRadioButton("Вещественные", this);
    mode_real->setFixedWidth(110);
    mode_complex = new QRadioButton("Комплексные", this);
    mode_complex->setFixedWidth(110);
    mode_rational = new QRadioButton("Рациональные", this);
    mode_rational->setFixedWidth(110);

    //изначально на рациональных
    mode_rational->setChecked(true);
    mode = RATIONAL_MODE;

    //поле ввода
    input = new QLineEdit(QString::number(size), this);
    input->setAlignment(Qt::AlignCenter);
    input->setFixedWidth(50);
    input->hide();

    // поле вывода
    output = new QLabel("", this);
    output->setFixedWidth(150);

    //выравнивание поля ввода
    input_layout = new QGroupBox(this);
    footer = new QHBoxLayout(input_layout);

    footer->addWidget(output);
    footer->addWidget(input);
    footer->addWidget(button_accept);
    footer->setAlignment(Qt::AlignLeft);

    //выравнивание кнопок
    buttons_layout = new QGroupBox(this);
    blayout = new QHBoxLayout(buttons_layout);

    blayout->addWidget(button_det);
    blayout->addWidget(button_rank);
    blayout->addWidget(button_transpose);
    blayout->addWidget(button_enter);

    //выравнивание выборов
    radiobut_layout = new QGroupBox(this);
    //radiobut_layout->setAlignment(Qt::AlignCenter);
    rlayout = new QHBoxLayout(radiobut_layout);

    rlayout->addWidget(mode_real);
    rlayout->addWidget(mode_complex);
    rlayout->addWidget(mode_rational);

    //
    grid_layout = new QGroupBox(this);
    grid = new QGridLayout(grid_layout);
    grid->setSpacing(50);

    //
    scrollArea = new QScrollArea(this);
    scrollArea->setWidget(grid_layout);
    scrollArea->setWidgetResizable(true);
    scrollArea->setMinimumSize(QSize(700, 400));
    scrollArea->setGeometry(0, 0, 700, 400);

    //рендеринг
    this->rendering();

    connect(button_enter, SIGNAL(pressed()), this, SLOT(enterDim()));
    connect(button_accept, SIGNAL(pressed()), this, SLOT(accept()));
    connect(button_det,SIGNAL(pressed()),this,SLOT(formRequest()));
    connect(button_rank,SIGNAL(pressed()),this,SLOT(formRequest()));
    connect(button_transpose, SIGNAL(pressed()), this, SLOT(formRequest()));

    connect(mode_real, SIGNAL(clicked()), this, SLOT(selectMode()));
    connect(mode_complex, SIGNAL(clicked()), this, SLOT(selectMode()));
    connect(mode_rational, SIGNAL(clicked()), this, SLOT(selectMode()));
}

TInterface::~TInterface()
{
    this->clear();
    delete button_det;
    delete button_rank;
    delete button_transpose;
    delete button_enter;
    delete button_accept;

    delete mode_real;
    delete mode_complex;
    delete mode_rational;

    delete output;
    delete input;

    delete radiobut_layout;
    delete buttons_layout;
    delete input_layout;
    delete grid_layout;

    delete blayout;
    delete rlayout;
    delete footer;
    delete grid;

    delete scrollArea;
}

void TInterface::selectMode()
{
    QRadioButton *m = (QRadioButton *) sender();
    if (m == mode_real) {
        mode = REAL_MODE;
        this->clear();
        this->rendering();
    }

    if (m == mode_complex) {
        mode = COMPLEX_MODE;
        this->clear();
        this->rendering();
    }

    if (m == mode_rational) {
        mode = RATIONAL_MODE;
        this->clear();
        this->rendering();
    }
}

void TInterface::formRequest()
{
    //msg = mode + size matrix + matrix + function
    input->hide();
    output->setFixedWidth(300);
    button_accept->hide();

    QString msg;

    //передаем режим работы
    msg << QString().setNum(mode);

    //передаем размер матрицы и саму матрицу
    msg << QString::number(size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            msg << numerator[i][j]->text();
            if (mode != REAL_MODE){
                msg << denominator[i][j]->text();
            }
        }
    }

    //передаем функцию
    QPushButton *btn = (QPushButton *) sender();
    if (btn == button_det)
        msg << QString().setNum(DETERMINANT);

    if (btn == button_rank)
        msg << QString().setNum(RANK);

    if (btn == button_transpose)
        msg << QString().setNum(TRANSPOSE);

    emit request(msg);
}

void TInterface::answer(QString msg)
{
    QString text;
    int p = msg.indexOf(separator);
    int operation = msg.left(p).toInt();
    //msg = msg.mid(p + 1, msg.length() - p - 2);
    msg = msg.right(msg.length() - p - 1);

    switch (operation) {
    case DETERMINANT:
    {
        text = "Определитель = ";
        p = msg.indexOf(separator);

        switch (mode) {
        case REAL_MODE: {
            double a = msg.left(p).toDouble();
            text += QString::number(a);
            break;
        }
        case COMPLEX_MODE: {
            int a = msg.left(p).toInt();
            msg = msg.right(msg.length() - p - 1);
            p = msg.indexOf(separator);
            int b = msg.left(p).toInt();
            text += "(" + QString::number(a) + ") + (" + QString::number(b) + "i)";
            break;
        }
        case RATIONAL_MODE: {
            int a = msg.left(p).toInt();
            msg = msg.right(msg.length() - p - 1);
            p = msg.indexOf(separator);
            int b = msg.left(p).toInt();
            text += QString::number(a) + "/" + QString::number(b);
            break;
        }
        }

        output->setText(text);
        break;
    }
    case RANK:
    {
        text = "Ранг = ";
        p = msg.indexOf(separator);
        text += QString::number(msg.left(p).toInt());
        output->setText(text);
        break;
    }
    case TRANSPOSE:
    {
        //qDebug() << msg;
        //заполнить матрицу
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                p = msg.indexOf(separator);
                numerator[i][j]->setText(QString::number(msg.left(p).toInt()));
                msg = msg.right(msg.length() - p - 1);

                if (mode != REAL_MODE){
                    p = msg.indexOf(separator);
                    denominator[i][j]->setText(QString::number(msg.left(p).toInt()));
                    msg = msg.right(msg.length() - p - 1);
                }
            }
        }

        output->setText("Матрица транспонирована");
        break;
    }
    default: break;
    }
}

void TInterface::rendering()
{
    // поля для матрицы
    this->allocate_memory();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            numerator[i][j]->setAlignment(Qt::AlignCenter);
            denominator[i][j]->setAlignment(Qt::AlignCenter);
        }
    }
    radiobut_layout->setGeometry(0, maximumHeight() - 150, maximumWidth(), 50);
    buttons_layout->setGeometry(0, maximumHeight() - 100, maximumWidth(), 50);
    input_layout->setGeometry(0, maximumHeight() - 50, maximumWidth(), 50);
}

void TInterface::allocate_memory()
{
    delimiter = new QLabel **[size];
    image = new QLabel **[size];

    numerator = new QLineEdit **[size];
    denominator = new QLineEdit **[size];
    numbers = new QHBoxLayout**[size];

    for (int i = 0; i < size; i++) {
        delimiter[i] = new QLabel *[size];
        image[i] = new QLabel *[size];

        numerator[i] = new QLineEdit *[size];
        denominator[i] = new QLineEdit *[size];

        numbers[i] = new QHBoxLayout *[size];
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            //logic mode
            delimiter[i][j] = new QLabel(this);
            image[i][j] = new QLabel("i", this);
            numerator[i][j] = new QLineEdit(QString::number(i + j), this);
            denominator[i][j] = new QLineEdit("1", this);

            denominator[i][j]->setFixedWidth(70);
            numerator[i][j]->setFixedWidth(70);
            delimiter[i][j]->setFixedWidth(8);
            image[i][j]->setFixedWidth(5);


            switch (mode) {
            case REAL_MODE:
                numerator[i][j]->setFixedWidth(100);
                delimiter[i][j]->hide();
                image[i][j]->hide();
                denominator[i][j]->hide();
                break;
            case COMPLEX_MODE:
                delimiter[i][j]->setText("+");
                delimiter[i][j]->show();
                image[i][j]->show();
                denominator[i][j]->show();
                break;
            case RATIONAL_MODE:
                delimiter[i][j]->setText("/");
                delimiter[i][j]->show();
                image[i][j]->hide();
                denominator[i][j]->show();
                break;
            }

            numbers[i][j] = new QHBoxLayout();
            numbers[i][j]->addWidget(numerator[i][j]);
            numbers[i][j]->addWidget(delimiter[i][j]);
            numbers[i][j]->addWidget(denominator[i][j]);
            numbers[i][j]->addWidget(image[i][j]);

            numbers[i][j]->setSpacing(5);

            grid->addLayout(numbers[i][j], i, j);
        }
    }


}

void TInterface::clear()
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            delete delimiter[i][j];
            delete image[i][j];

            delete numerator[i][j];
            delete denominator[i][j];
            delete numbers[i][j];
        }
    }

    for (int i = 0; i < size; i++) {
        delete[] delimiter[i];
        delete[] image[i];

        delete[] numerator[i];
        delete[] denominator[i];
        delete[] numbers[i];
    }

    delete[] delimiter;
    delete[] image;
    delete[] numerator;
    delete[] denominator;
    delete[] numbers;
}

void TInterface::enterDim()
{
    output->setFixedWidth(150);
    output->setText("Введите размер матрицы: ");
    input->show();
    button_accept->show();
}

void TInterface::accept()
{
    int s = input->text().toInt();
    this->clear();
    this->size = s;
    this->rendering();
}





