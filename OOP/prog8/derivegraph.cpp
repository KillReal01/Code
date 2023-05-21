#include "derivegraph.h"
#include <math.h>
#include <QDebug>

TDeriveGraph::TDeriveGraph() {}

TDeriveGraph::TDeriveGraph(TMatrix<qint16> &matrix)
{
    this->count = matrix.getRow();
    this->matrix = matrix;
    active = 0;
}

TDeriveGraph::TDeriveGraph(const TGraph &graph)
    : TGraph(graph)
{
    active = 0;
}

void TDeriveGraph::draw(QPainter *p, QRect r, QColor c)
{
    TGraph::drawPoints(p, r, active, Qt::green);
    TGraph::drawLinks(p, active);

    qreal cw = 0.5 * r.width();
    qreal ch = 0.5 * r.height();
    qreal cr = 0.8 * (cw > ch ? ch : cw);
    qreal a = 2.0 * acos(-1.0) / count;
    int radius = 19;

    int i = active;
    int x = cw + cr * sin(i * a);
    int y = ch - cr * cos(i * a);

    p->setPen(QPen(Qt::black, 1, Qt::SolidLine));
    p->setBrush(QBrush(c));
    p->drawEllipse(QPoint(x, y), radius, radius);

    int k = 16;
    p->drawText(QRectF(x - k + 1, y - k, 2 * k, 2 * k),
                QString().setNum(i + 1),
                QTextOption(Qt::AlignCenter));


}

void TDeriveGraph::newEvent(bool direction)
{
    if (direction) active++;
    else active = --active + count;
    active = active % count;
}
