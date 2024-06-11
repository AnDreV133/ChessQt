#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <QString>
#include <QPoint>

class Utils {
public:
    static const char* toCharArr(int x) {
        return std::to_string(x).c_str();
    }

    static QString toQString(std::string str) {
        return QString(str.c_str());
    }

    static QPoint toScenePos(QPoint pos, int sideSize) {
        return QPoint(pos.x() * sideSize, pos.y() * sideSize);
    }

    static QPoint toPos(QPoint scenePos, int sideSize) {
        return QPoint(scenePos.x() / sideSize, scenePos.y() / sideSize);
    }

    // static QString toQString(int x) {
    //     return QString(toCharArr(x));
    // }
};

#endif // UTILS_H
