#ifndef TDERIVEGRAPH_H
#define TDERIVEGRAPH_H

#include "graph.h"
#include "matrix.h"

class TDeriveGraph : public TGraph
{
    int active;

public:
    TDeriveGraph();
    TDeriveGraph(TMatrix<qint16> &);
    TDeriveGraph(const TGraph &);
    void draw(QPainter *, QRect, QColor);
    void newEvent(bool);
};

#endif // TDERIVEGRAPH_H
