#ifndef ROOK_H
#define ROOK_H

#include "figure.h"
#include "behavior/straightaction.h"

class Rook : public Figure {
public:
    Rook(FigureColor figureColor)
        : Figure(figureColor, "rook", new StraightAction()) {
        setPathToImage(figureColor, "R");
    }
};

#endif // ROOK_H
