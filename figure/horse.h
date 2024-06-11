#ifndef HORSE_H
#define HORSE_H

#include "figure.h"
#include "behavior/horseaction.h"

class Horse : public Figure {
public:
    Horse(FigureColor figureColor)
        : Figure(figureColor, "horse", new HorseAction()) {
        setPathToImage(figureColor, "H");
    }
};

#endif // HORSE_H
