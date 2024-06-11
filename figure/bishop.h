#ifndef BISHOP_H
#define BISHOP_H

#include "figure.h"
#include "behavior/diagonalaction.h"

#include <QCoreApplication>

class Bishop : public Figure {
public:
    Bishop(FigureColor figureColor)
        : Figure(figureColor, "bishop", new DiagonalAction()) {
        setPathToImage(figureColor, "B");
    }
};

#endif // BISHOP_H
