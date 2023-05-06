#include "interface.h"
#include <iostream>
#include "matrix.h"

TInterface::TInterface(QWidget *parent)
    : QWidget{parent}
{
    setWindowTitle("Работа №7");
    setFixedSize(500, 520);

    //labels
    choose_file = new QLabel("Выберите файл для загрузки графа", this);

    //buttons
    btn_search = new QPushButton("Обзор", this);
    btn_load = new QPushButton("Нарисовать граф", this);

    //lineedit
    filepath = new QLineEdit(this);

    //layoyt
    text = new QWidget(this);
    text->setFixedSize(400, 100);
    text->move((this->width() - text->width()) / 2, 410);

    grid = new QGridLayout(text);
    grid->addWidget(choose_file, 0, 0);
    grid->addWidget(filepath, 1, 0);
    grid->addWidget(btn_search, 1, 1);
    grid->addWidget(btn_load, 2, 0);



    connect(btn_search, SIGNAL(clicked()), this, SLOT(search_file()));
    connect(btn_load, SIGNAL(clicked()), this, SLOT(load_graph()));
}

TInterface::~TInterface()
{
    delete choose_file;
    delete grid;
    delete text;
}

void TInterface::search_file()
{
    QString initialDir = QCoreApplication::applicationDirPath();
    filepath->setText(QFileDialog::getOpenFileName(this,
                                                   "Выберите файл",
                                                   initialDir,
                                                   "Текстовые файлы (*.txt);;Все файлы (*)"));
}

void TInterface::load_graph()
{
    QFile file(filepath->text());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "can't open file";
        return;
    }

    QTextStream in(&file);
    QVector<QVector<qint16>> data;

    while (!in.atEnd()) {
        QStringList list = in.readLine().split(" ");
        QVector<qint16> vec;

        for (int i = 0; i < list.size(); i++) {
            vec.append(list[i].toInt());
        }
        data.append(vec);
    }

    int size = data.size();
    TMatrix<qint16> mtx(size, size, data);

    TGraph graph(mtx);
    delete canvas;
    canvas = new TCanvas(graph, this);
    canvas->move((this->width() - canvas->width()) / 2, 10);
    canvas->show();
}
