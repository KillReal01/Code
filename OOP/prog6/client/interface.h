#ifndef TINTERFACE_H
#define TINTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QRadioButton>
#include <QSpacerItem>

class TInterface : public QWidget
{
    Q_OBJECT;

private:
    int mode;
    QLineEdit ***numerator, ***denominator, *input;
    QLabel ***delimiter, ***image;
    QLabel *output;
    QPushButton *button_det, *button_rank, *button_transpose, *button_enter, *button_accept;
    QGroupBox *buttons_layout, *input_layout, *grid_layout, *radiobut_layout;
    QHBoxLayout *blayout, *footer, ***numbers, *rlayout;
    QGridLayout *grid;
    QScrollArea *scrollArea;
    QRadioButton *mode_real, *mode_complex, *mode_rational;

    int size = 3;

    void clear();
    void rendering();
    void allocate_memory();

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();

public slots:
    void enterDim();
    void accept();

public slots:
    void answer(QString);

private slots:
    void formRequest();
    void selectMode();

signals:
    void request(QString);


};
#endif // TINTERFACE_H
