#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include "graph.h"

class TCanvas : public QWidget
{
    //Q_OBJECT

    TGraph graph;
public:
    TCanvas(TGraph, QWidget *parent = 0);
    ~TCanvas();

protected:
    void paintEvent(QPaintEvent*);
};

#endif // VIEWER_H
