#ifndef NONEFIGURE_H
#define NONEFIGURE_H

#include "figure.h"
#include "behavior/noaction.h"

class NoneFigure : public Figure {
public:
    NoneFigure() : Figure(FigureColor::DEFAULT, "", new NoAction()) {}
};

#endif // NONEFIGURE_H
