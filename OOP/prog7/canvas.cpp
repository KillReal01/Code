#include "canvas.h"

TCanvas::TCanvas(TGraph graph, QWidget *parent)
    : QWidget(parent)
{
    this->graph = graph;
    setFixedSize(500, 500);
    this->setStyleSheet("background-color: white;");
}

TCanvas::~TCanvas()
{

}

void TCanvas::paintEvent(QPaintEvent*)
{
    QPainter p;
    p.begin(this);
    graph.drawPoints(&p, rect(), Qt::green);
    graph.drawLinks(&p);
    p.end();
}
