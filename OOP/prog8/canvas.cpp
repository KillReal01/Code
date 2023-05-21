#include "canvas.h"

TCanvas::~TCanvas() {}

TCanvas::TCanvas(TDeriveGraph graph, QWidget *parent)
    : QWidget(parent)
{
    derive = new TDeriveGraph(graph);
    setFixedSize(500, 500);
    this->setStyleSheet("background-color: white;");
}

void TCanvas::paintEvent(QPaintEvent*)
{
    QPainter p;
    p.begin(this);
    derive->draw(&p, rect(), Qt::yellow);
    p.end();
}

void TCanvas::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        derive->newEvent(false);
    }
    if (event->button() == Qt::RightButton) {
        derive->newEvent(true);
    }
    update();
}
