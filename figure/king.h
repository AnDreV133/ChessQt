#ifndef KING_H
#define KING_H

#include "figure.h"
#include "behavior/alldirectionsaction.h"

class King : public Figure {
public:
    King(FigureColor figureColor)
        : Figure(figureColor, "king", new AllDirectionsBehavior()) {
        setPathToImage(figureColor, "K");
    }
};

#endif // KING_H
