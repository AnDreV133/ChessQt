#ifndef FIGURE_H
#define FIGURE_H

#include "behavior/actionbehavior.h"
#include "../enums.h"
#include <cstdio>
#include <string>
#include <QString>
#include <QCoreApplication>

class Figure {
public:
    bool const moveEqualAttack;
    FigureColor const figureColor;
    QString const name;

    Figure(
            FigureColor figureColor,
            QString name,
            ActionBehavior *moveWithAttackBehavior
        ) : moveEqualAttack(true),
            figureColor(figureColor),
            name(name),
            movePerform(moveWithAttackBehavior),
            attackPerform(moveWithAttackBehavior) {
        filePathToImage = filePathToImage;
    }

    Figure(
            FigureColor figureColor,
            QString name,
            ActionBehavior *moveBehavior,
            ActionBehavior *attackBehavior
        ) : moveEqualAttack(false),
            figureColor(figureColor),
            name(name),
            movePerform(moveBehavior),
            attackPerform(attackBehavior) {
        filePathToImage = filePathToImage;
    }

    uint64_t move(uint64_t bitboard, uint64_t blocking) {
        return movePerform->action(bitboard, blocking);
    }

    uint64_t attack(uint64_t bitboard, uint64_t blocking) {
        return attackPerform->action(bitboard, blocking);
    }

    ~Figure() {
        delete movePerform;
        if (!moveEqualAttack)
            delete attackPerform;
    }

    QString getFilePathToImage() {
        return filePathToImage;
    }

protected:
    QString filePathToImage;

    void setPathToImage(FigureColor figureColor, const char* name) {
        QString res;
        char colorDir[7];
        if (figureColor == FigureColor::WHITE)
            sprintf(colorDir, "white/");
        else if (figureColor == FigureColor::BLACK)
            sprintf(colorDir, "black/");
        else
            return;

        filePathToImage = QString()
                              .append(":/").append("resources/").append(colorDir)
                              .append(name).append(".png");
    }

private:
    ActionBehavior *movePerform;
    ActionBehavior *attackPerform;
};

#endif // FIGURE_H
