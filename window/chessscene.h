#ifndef CHESSSCENE_H
#define CHESSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsItem>

#include "cellgraphicitem.h"
#include "figuregraphicitem.h"
#include "highlitegraphicitem.h"

#include "../gamemode/chesslogger.h"

// class FigureGraphicItem;

class ChessScene : public QGraphicsScene {
    Q_OBJECT

public:
    ChessScene(int sceneSize, GameMode* gameMode, QObject *parent = nullptr) : QGraphicsScene(parent) {
        // cellsGraphicItems = new std::vector<CellGraphicItem*>;
        highlitesGraphicItems = new std::vector<HighliteGraphicItem*>;
        figuresGraphicItems = new std::vector<std::vector<FigureGraphicItem*>>(SIDE_SIZE_IN_CELL, std::vector<FigureGraphicItem*>(SIDE_SIZE_IN_CELL));
        allowedPoses = new std::vector<QPoint>;

        this->gameMode = gameMode;

        this->sceneSize = sceneSize;
        sideSize = sceneSize / SIDE_SIZE_IN_CELL;

        bool isWhite = true;
        for (int i = 0; i < sceneSize; i += sideSize) {
            for (int j = 0; j < sceneSize; j += sideSize) {
                CellGraphicItem* it = new CellGraphicItem(QPoint(j, i), sideSize, isWhite);
                it->setZValue(0);
                addItem(it);
                isWhite = !isWhite;
            }
            isWhite = !isWhite;
        }

        for (int y = 0; y < SIDE_SIZE_IN_CELL; ++y) {
            for (int x = 0; x < SIDE_SIZE_IN_CELL; ++x) {
                Figure* figure = gameMode->getFigurePlacementInv()[GameMode::invCoord(y)][x];
                if (figure != nullptr) {
                    FigureGraphicItem *it
                        = new FigureGraphicItem(Utils::toScenePos(QPoint(x, y), sideSize), sideSize);

                    (*figuresGraphicItems)[y][x] = it;
                    QString filePath = figure->getFilePathToImage();
                    it->setFigurePixmap(filePath);
                    it->setZValue(2);
                    addItem(it);
                }
            }
        }
    }

    ~ChessScene() {
        // delete cellsGraphicItems;
        delete highlitesGraphicItems;
        delete figuresGraphicItems;
    }



private:
    // std::vector<CellGraphicItem*> *cellsGraphicItems;
    std::vector<HighliteGraphicItem*> *highlitesGraphicItems;
    std::vector<QPoint> *allowedPoses;
    std::vector<std::vector<FigureGraphicItem*>> *figuresGraphicItems;

    GameMode *gameMode;

    int sceneSize;
    int sideSize;

    QPoint startPos;

    static const int SIDE_SIZE_IN_CELL = 8;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        removeHighlite();

        startPos = Utils::toPos(event->scenePos().toPoint(), sideSize);
        allowedPoses = gameMode->checkFigure(Utils::toPos(event->scenePos().toPoint(), sideSize));

        addHighlite();
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override {
        for (QPoint endPos : *allowedPoses)
            if (endPos == Utils::toPos(event->scenePos().toPoint(), sideSize)) {
                gameMode->moveFigure(startPos, endPos);
                gameMode->switchTurn();

                FigureGraphicItem *temp = (*figuresGraphicItems)[endPos.y()][endPos.x()];
                if(temp != nullptr) delete temp;
                (*figuresGraphicItems)[endPos.y()][endPos.x()] = (*figuresGraphicItems)[startPos.y()][startPos.x()];
                (*figuresGraphicItems)[endPos.y()][endPos.x()]->setPos(Utils::toScenePos(endPos, sideSize));
                if((*figuresGraphicItems)[startPos.y()][startPos.x()] != nullptr) (*figuresGraphicItems)[startPos.y()][startPos.x()] = nullptr;

                emit signalNewLog(gameMode->getNewLogMsg());
                emit signalOtherTurn();

                break;
            }

        removeHighlite();
    }

    void removeHighlite() {
        allowedPoses->clear();
        for (HighliteGraphicItem* it : *highlitesGraphicItems)
            removeItem(it);
        highlitesGraphicItems->clear();
    }

    void addHighlite() {
        for (QPoint it : *allowedPoses) {
            HighliteGraphicItem* newHighliteGraphicItem
                = new HighliteGraphicItem(Utils::toScenePos(it, sideSize), sideSize, !gameMode->isConteinFigureByPos(it));
            newHighliteGraphicItem->setZValue(1);

            highlitesGraphicItems->push_back(newHighliteGraphicItem);

            addItem(newHighliteGraphicItem);
        }
    }

signals:
    void signalOtherTurn();
    void signalNewLog(QString log);
};

#endif // CHESSSCENE_H

