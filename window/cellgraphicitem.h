#ifndef CELLGRAPHICITEM_H
#define CELLGRAPHICITEM_H

#include <QGraphicsView>

class CellGraphicItem : public QGraphicsRectItem {
public:
    CellGraphicItem(QPoint scenePos, int size, bool isWhite, QGraphicsItem* parent = nullptr)
        : QGraphicsRectItem(scenePos.x(), scenePos.y(), size, size, parent) {
        setBrush(isWhite ? Qt::white : Qt::lightGray);
    }
};

#endif // CELLGRAPHICITEM_H
