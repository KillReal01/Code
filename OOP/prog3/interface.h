#ifndef TINTERFACE_H
#define TINTERFACE_H

#include "matrix.h"
#include "number.h"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QGridLayout>

class TInterface : public QWidget
{
    Q_OBJECT;

private:
    QLineEdit ***numerator, ***denominator, *input;
    QLabel ***delimiter;
    QLabel *output;
    QPushButton *button_det, *button_rank, *button_transpose, *button_enter, *button_accept;
    QGroupBox *buttons_layout, *input_layout, *grid_layout;
    QHBoxLayout *layout, *footer, ***numbers;
    QGridLayout *grid;
    int size = 3;

    void clear();
    void rendering();
    void allocate_memory();

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();

public slots:
    void getDet();
    void getRank();
    void transposeMtx();
    void enterDim();
    void accept();
};
#endif // TINTERFACE_H
