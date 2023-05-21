#ifndef TGRAPH_H
#define TGRAPH_H

#include <QPainter>
#include "matrix.h"

class TGraph
{
protected:
    int count;
    TMatrix<qint16> matrix;

private:
    QVector<QPointF> points;
    void drawArrowLine(QPainter *painter, const QPointF &p1, const QPointF &p2);

public:
    TGraph();
    TGraph(TMatrix<qint16> &matrix);
    void drawPoints(QPainter *, QRect, int, QColor);
    void drawLinks(QPainter *p, int);
};

#endif // TGRAPH_H
