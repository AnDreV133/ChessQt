#ifndef QUEEN_H
#define QUEEN_H

#include "figure.h"
#include "behavior/allslidedirectionaction.h"

class Queen : public Figure {
public:
    Queen(FigureColor figureColor)
        : Figure(figureColor, "queen", new AllSlideDirectionAction()) {
        setPathToImage(figureColor, "Q");
    }
};

#endif // QUEEN_H
