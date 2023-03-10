#include "interface.h"

TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Работа №3");
    setFixedSize(700, 500);

    // поля для кнопок
    button_det = new QPushButton("Определитель", this);
    button_rank = new QPushButton("Ранг", this);
    button_transpose = new QPushButton("Транспонировать", this);
    button_enter = new QPushButton("Ввести размер", this);
    button_accept = new QPushButton("Задать размер", this);
    button_accept->setFixedWidth(100);
    button_accept->hide();

    //поле ввода
    input = new QLineEdit(QString::number(size), this);
    input->setAlignment(Qt::AlignCenter);
    input->setFixedWidth(50);
    input->hide();

    // поле вывода
    output = new QLabel("", this);
    output->setFixedWidth(150);
    //выравнивание


    input_layout = new QGroupBox(this);
    footer = new QHBoxLayout(input_layout);

    footer->addWidget(output);
    footer->addWidget(input);
    footer->addWidget(button_accept);
    footer->setAlignment(Qt::AlignLeft);

    //
    buttons_layout = new QGroupBox(this);
    layout = new QHBoxLayout(buttons_layout);

    layout->addWidget(button_det);
    layout->addWidget(button_rank);
    layout->addWidget(button_transpose);
    layout->addWidget(button_enter);

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

    connect(button_det, SIGNAL(pressed()), this, SLOT(getDet()));
    connect(button_rank, SIGNAL(pressed()), this, SLOT(getRank()));
    connect(button_transpose, SIGNAL(pressed()), this, SLOT(transposeMtx()));
    connect(button_enter, SIGNAL(pressed()), this, SLOT(enterDim()));
    connect(button_accept, SIGNAL(pressed()), this, SLOT(accept()));
}

TInterface::~TInterface()
{
    this->clear();
    delete button_det;
    delete button_rank;
    delete button_transpose;
    delete button_enter;
    delete button_accept;

    delete output;
    delete input;

    delete buttons_layout;
    delete input_layout;
    delete grid_layout;
    delete layout;
    delete footer;
    delete grid;

    delete scrollArea;
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
    buttons_layout->setGeometry(0, maximumHeight() - 100, maximumWidth(), 50);
    input_layout->setGeometry(0, maximumHeight() - 50, maximumWidth(), 50);
}

void TInterface::allocate_memory()
{
    delimiter = new QLabel **[size];
    numerator = new QLineEdit **[size];
    denominator = new QLineEdit **[size];
    numbers = new QHBoxLayout**[size];

    for (int i = 0; i < size; i++) {
        delimiter[i] = new QLabel *[size];
        numerator[i] = new QLineEdit *[size];
        denominator[i] = new QLineEdit *[size];
        numbers[i] = new QHBoxLayout *[size];
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            delimiter[i][j] = new QLabel("/", this);
            delimiter[i][j]->setFixedWidth(5);

            numerator[i][j] = new QLineEdit(QString::number(i + j), this);
            numerator[i][j]->setFixedWidth(70);

            denominator[i][j] = new QLineEdit("1", this);
            denominator[i][j]->setFixedWidth(70);

            numbers[i][j] = new QHBoxLayout();
            numbers[i][j]->addWidget(numerator[i][j]);
            numbers[i][j]->addWidget(delimiter[i][j]);
            numbers[i][j]->addWidget(denominator[i][j]);
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
            delete numerator[i][j];
            delete denominator[i][j];
            delete numbers[i][j];
        }
    }

    for (int i = 0; i < size; i++) {
        delete[] delimiter[i];
        delete[] numerator[i];
        delete[] denominator[i];
        delete[] numbers[i];
    }

    delete[] delimiter;
    delete[] numerator;
    delete[] denominator;
    delete[] numbers;
}

void TInterface::getDet()
{
    input->hide();
    button_accept->hide();
    TMatrix a(size, numerator, denominator);
    QString answer = "Определитель = ";
    number det = a.det();
    answer << det;
    output->setText(answer);
}

void TInterface::getRank()
{
    input->hide();
    button_accept->hide();
    TMatrix a(size, numerator, denominator);
    QString answer = "Ранг = " + QString::number(a.rank());
    output->setText(answer);
}

void TInterface::transposeMtx()
{
    input->hide();
    button_accept->hide();
    TMatrix a(size, numerator, denominator);
    a.transpose();
    a.getMtx(numerator, denominator);
    output->setText("Матрица транспонирована");
}

void TInterface::enterDim()
{
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





