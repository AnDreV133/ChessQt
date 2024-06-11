#ifndef HIGHLITEGRAPHICITEM_H
#define HIGHLITEGRAPHICITEM_H

#include <QGraphicsItem>

class HighliteGraphicItem : public QGraphicsRectItem {
public:
    HighliteGraphicItem(QPoint scenePos, int size, bool isEnemy, QGraphicsItem *parent = nullptr)
        : QGraphicsRectItem(scenePos.x(), scenePos.y(), size, size, parent) {
        setBrush(isEnemy ? Qt::green : Qt::red);
    }
};

#endif // HIGHLITEGRAPHICITEM_H
