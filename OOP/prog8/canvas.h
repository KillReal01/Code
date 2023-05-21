#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QMouseEvent>
#include "derivegraph.h"

class TCanvas : public QWidget
{
    //Q_OBJECT

    TDeriveGraph *derive;
public:
    TCanvas(TDeriveGraph, QWidget *parent = 0);
    ~TCanvas();

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
};

#endif // VIEWER_H
