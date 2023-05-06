#ifndef TINTERFACE_H
#define TINTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QCoreApplication>
#include "canvas.h"


#include <QString>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QRadioButton>
#include <QSpacerItem>

class TInterface : public QWidget
{
    Q_OBJECT
public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();

private:
    TCanvas *canvas = nullptr;
    QLabel *choose_file;
    QPushButton *btn_search, *btn_load;
    QLineEdit *filepath;
    QGridLayout *grid;
    QWidget *text;


public slots:
    void search_file();
    void load_graph();
};

#endif // TINTERFACE_H
