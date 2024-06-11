#ifndef FIGUREGRAPHICITEM_H
#define FIGUREGRAPHICITEM_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <vector>

#include "../gamemode/gamemode.h"
#include "../utils.h"

class FigureGraphicItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    FigureGraphicItem(QPoint scenePos, int size, const QString fileNameToFigureImage, QGraphicsItem *parent = nullptr)
        : QGraphicsPixmapItem(parent) {
        this->size = size;
        setPos(scenePos.x(), scenePos.y());
        setFigurePixmap(fileNameToFigureImage);
    }

    FigureGraphicItem(QPoint scenePos, int size, QGraphicsItem *parent = nullptr)
        : QGraphicsPixmapItem(parent) {
        this->size = size;
        setPos(scenePos.x(), scenePos.y());
    }

    void setFigurePixmap(QString fileNameToFigureImage) {
        qDebug() << fileNameToFigureImage << "set pixmap";
        QImage image(fileNameToFigureImage);
        setPixmap(QPixmap::fromImage(image).scaled(size, size));
    }

private:
    int size;
};

#endif // FIGUREGRAPHICITEM_H
