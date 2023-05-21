#include "graph.h"
#include <math.h>
#include <QPainterPath>


TGraph::TGraph() {}

TGraph::TGraph(TMatrix<qint16> &matrix)
    : count(matrix.getRow())
    , matrix(matrix)
{}

void TGraph::drawPoints(QPainter *p, QRect r, int active, QColor c)
{
    qreal cw = 0.5 * r.width();
    qreal ch = 0.5 * r.height();
    qreal cr = 0.8 * (cw > ch ? ch : cw);
    qreal a = 2.0 * acos(-1.0) / count;
    int radius = 19;

    p->setPen(QPen(Qt::black, 2, Qt::DotLine));
    p->drawEllipse(QPoint(int(cw), int(ch)), int(cr), int(cr));

    QFont font;
    font.setPointSize(20);
    p->setFont(QFont(font));
    points.clear();

    for (int i = 0; i < count; i++) {
        int x = cw + cr * sin(i * a);
        int y = ch - cr * cos(i * a);

        p->setPen(QPen(Qt::black, 2, Qt::SolidLine));
        p->setBrush(QBrush(Qt::white));
        int x_loop = cw + (cr + 20) * sin(i * a);
        int y_loop = ch - (cr + 20) * cos(i * a);
        if (matrix[i][i] == 1 && i == active) //петля
        {
            p->drawEllipse(QPoint(x_loop, y_loop), int(1.2 * radius), int(1.2 * radius));
        }
        p->setPen(QPen(Qt::black, 1, Qt::SolidLine));
        p->setBrush(QBrush(c));
        p->drawEllipse(QPoint(x, y), radius, radius);
        int x_link = cw + (cr - 20) * sin(i * a);
        int y_link = ch - (cr - 20) * cos(i * a);
        points.append(QPointF(x_link, y_link));

        int k = 16;
        p->drawText(QRectF(x - k + 1, y - k, 2 * k, 2 * k),
                    QString().setNum(i + 1),
                    QTextOption(Qt::AlignCenter));
    }
}

void TGraph::drawLinks(QPainter *p, int active)
{
    p->setPen(QPen(Qt::black, 2, Qt::SolidLine));
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (matrix[i][j] == 1 && i == active) // есть связь между точками
            {
                drawArrowLine(p, points[i], points[j]);
            }
        }
    }
}

void TGraph::drawArrowLine(QPainter *painter, const QPointF &p1, const QPointF &p2)
{
    painter->setBrush(QBrush(Qt::black));
    painter->drawLine(p1, p2);

    // вычисляем направление линии
    QLineF line(p1, p2);
    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = M_PI * 2.0 - angle;


    // рассчитываем координаты стрелки
    int k = 3.0;
    QPointF arrowP1 = p2 + QPointF(sin(angle - M_PI / k) * 15, cos(angle - M_PI / k) * 15);
    QPointF arrowP2 = p2
                      + QPointF(sin(angle - M_PI + M_PI / k) * 15,
                                cos(angle - M_PI + M_PI / k) * 15);

    // рисуем стрелку
    QPainterPath path(p2);
    path.lineTo(arrowP1);
    path.lineTo(arrowP2);
    path.closeSubpath();
    painter->drawPath(path);
}


