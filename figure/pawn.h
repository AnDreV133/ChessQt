#ifndef PAWN_H
#define PAWN_H

#include "figure.h"
#include "behavior/pawnaction.h"

class PawnWhite : public Figure {
public:
    PawnWhite()
        : Figure(FigureColor::WHITE, "pawn", new PawnWhiteMove(), new PawnWhiteAttack()) {
        setPathToImage(figureColor, "P");
    }
};

class PawnBlack : public Figure {
public:
    PawnBlack()
        : Figure(FigureColor::BLACK, "pawn", new PawnBlackMove(), new PawnBlackAttack()) {
        setPathToImage(figureColor, "P");
    }
};

#endif // PAWN_H
