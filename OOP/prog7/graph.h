#ifndef TGRAPH_H
#define TGRAPH_H

#include <QPainter>
#include "matrix.h"

class TGraph
{
    int count;
    TMatrix<qint16> matrix;
    QVector<QPointF> points;
    void drawArrowLine(QPainter *painter, const QPointF &p1, const QPointF &p2);
public:
    TGraph();
    TGraph(TMatrix<qint16> &matrix);
    void drawPoints(QPainter *, QRect, QColor);
    void drawLinks(QPainter *p);
};

#endif // TGRAPH_H
