#ifndef GAMEMODE_H
#define GAMEMODE_H

#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
#include <QPoint>
#include <QTimer>
#include <QTime>

#include "../figure/figure.h"
#include "../figure/nonefigure.h"
#include "../figure/king.h"
#include "../figure/bishop.h"
#include "../figure/horse.h"
#include "../figure/pawn.h"
#include "../figure/rook.h"
#include "../figure/queen.h"
#include "../settings/settingsjson.h"
#include "../utils.h"
#include "../figure/behavior/actionbehavior.h"

#include "chesslogger.h"

class GameMode {
public:
    GameMode() {
        SettingsJson::updateParametresFromJsonFile(settings);
    }

    ~GameMode() {

    }

    bool isConteinFigureByPos(QPoint realPos) {
        QPoint pos = QPoint(realPos.x(), invCoord(realPos.y()));
        return figurePlacement[pos.y()][pos.x()];
    }

    std::vector<std::vector<Figure*>> getFigurePlacementInv() {
        return figurePlacement;
    }

    virtual std::vector<QPoint> *checkFigure(QPoint realPos) {
        QPoint pos = QPoint(realPos.x(), invCoord(realPos.y()));

        qDebug() << realPos << "by click" << pos << "for bitboard";

        Figure *figure = figurePlacement[pos.y()][pos.x()];
        if (figure != nullptr && figure->figureColor == turnColor) {
            std::vector<QPoint> *res
                = getPosesWithoutAlly(pos, [figure](uint64_t bb, uint64_t bl){return figure->move(bb,bl);});

            if (!figure->moveEqualAttack) {
                std::vector<QPoint> *buf
                    = getPosesWithoutAlly(pos, [figure](uint64_t bb, uint64_t bl){return figure->attack(bb,bl);});
                res->insert(res->begin(), buf->begin(), buf->end());
            }

            return res;
        }

        return new std::vector<QPoint>();
    }

    virtual bool moveFigure(QPoint realPos, QPoint realTarget) {
        qDebug() << "realPos:" << realPos << realTarget;

        QPoint pos = QPoint(realPos.x(), invCoord(realPos.y()));
        QPoint target = QPoint(realTarget.x(), invCoord(realTarget.y()));

        qDebug() << "pos:" << pos << target;
        if (figurePlacement[pos.y()][pos.x()]->figureColor == turnColor) {
            logMsg = ChessLogger::moving(pos, target, figurePlacement[pos.y()][pos.x()]);

            Figure *temp = figurePlacement[target.y()][target.x()];
            if (temp != nullptr) delete temp;
            figurePlacement[target.y()][target.x()] = figurePlacement[pos.y()][pos.x()];
            if (figurePlacement[pos.y()][pos.x()] != nullptr) figurePlacement[pos.y()][pos.x()] = nullptr;

            figureDispositionBitboard = figureDispositionBitboard & ~convertPosToBitboard(pos) | convertPosToBitboard(target);

            return true;
        }

        return false;
    }

    QString getNewLogMsg() {
        return logMsg;
    }

    virtual void switchTurn() { qWarning() << "switchTurn not realized"; }

    static int invCoord(int coord) {
        return BOARD_SIDE - coord - 1;
    }

    QTime timeLeftPlayerOne;
    QTime timeLeftPlayerTwo;

protected:
    QString logMsg;

    SettingsJson settings;

    std::vector<std::vector<Figure*>> figurePlacement;

    FigureColor turnColor = FigureColor::WHITE;

    uint64_t figureDispositionBitboard;

    std::vector<std::vector<Figure*>> convertFileFromSettingsToDisposition() {
        QFile in(Utils::toQString(settings.fileNameOfFigureDisposition));
        if (in.open(QIODevice::ReadOnly)) {
            QTextStream stream(&in);

            std::string customDisposition = stream.readAll().toStdString();

            in.close();
            return convertStringToDisposition(customDisposition);
        }

        return convertStringToDisposition(classicDisposition);

    }

    std::vector<QPoint> *getPosesWithoutAlly(QPoint& pos, std::function<uint64_t(uint64_t, uint64_t)> action) {
        std::vector<QPoint> *resNotProcessed = convertBitboardToPoses(
            action(
                convertPosToBitboard(pos),
                figureDispositionBitboard
                )
            );

        qDebug() << convertPosToBitboard(pos);
        for (auto it : *resNotProcessed) {
            qDebug() << it;
        }

        std::vector<QPoint> *res = new std::vector<QPoint>;
        for (QPoint it : *resNotProcessed) {
            if (this->figurePlacement[it.y()][it.x()] == nullptr
                || this->figurePlacement[it.y()][it.x()]->figureColor != this->turnColor)
                res->push_back(it);
        }

        delete resNotProcessed;

        for (QPoint &it : *res) {
            it.setY(invCoord(it.y()));
            qDebug() << it;
        }

        return res;
    }

    static const int BOARD_SIDE = 8;

    static std::vector<std::vector<Figure*>> convertStringToDisposition(std::string disposition) {
        std::vector<std::vector<Figure*>> res(BOARD_SIDE, std::vector<Figure*>(BOARD_SIDE));
        int shift = 0; // for protection from other symbols
        int iterWrite = 0;
        int iterRead = 0;
        while (iterRead < BOARD_SIDE * BOARD_SIDE + shift) {
            Figure *figure = nullptr;
            char c = disposition[iterRead];
            switch (toupper(c)) {
            case 'R':
                figure = new Rook(defineColorByChar(c));
                break;
            case 'H':
                figure = new Horse(defineColorByChar(c));
                break;
            case 'B':
                figure = new Bishop(defineColorByChar(c));
                break;
            case 'Q':
                figure = new Queen(defineColorByChar(c));
                break;
            case 'K':
                figure = new King(defineColorByChar(c));
                break;
            case 'P':
                figure = defineColorByChar(c) == FigureColor::WHITE
                             ? static_cast<Figure*>(new PawnWhite)
                             : static_cast<Figure*>(new PawnBlack);
                break;
            // case 'A': // assassin - horse att bishop move
            //     break;

            // case 'S': // spearman - rook att king move
            //     break;
            case '.':
                iterWrite++;
                break;
            default:
                shift++;
                break;
            }

            if (figure != nullptr) {
                res[invCoord(iterWrite / BOARD_SIDE)][iterWrite % BOARD_SIDE] = figure;
                iterWrite++;
            }

            iterRead++;
        }

        return res;
    }

    inline static const std::string classicDisposition =
        "RHBQKBHR\
        PPPPPPPP\
        ........\
        ........\
        ........\
        ........\
        pppppppp\
        rhbqkbhr";

    static FigureColor defineColorByChar(int c) {
        return islower(c) ? FigureColor::WHITE : FigureColor::BLACK;
    }

    static uint64_t convertPosToBitboard(QPoint pos) {
        return (1ULL << (pos.y() * 8ULL + pos.x()));
    }

    static std::vector<QPoint>* convertBitboardToPoses(uint64_t bitboard) {
        std::vector<QPoint>* res = new std::vector<QPoint>;

        for (int i = 0; i < BOARD_SIDE * BOARD_SIDE; i++) {
            if ((bitboard >> i) & 1)
                res->push_back(QPoint(i % BOARD_SIDE, i / BOARD_SIDE));
        }

        return res;
    }

    static uint64_t convertDispositionToBitboard(std::vector<std::vector<Figure*>> disposition) {
        uint64_t bitboard = 0ULL;

        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                Figure *figure = disposition[y][x];
                if (figure != nullptr) {
                    uint64_t square = 1ULL << (y * 8 + x);
                    bitboard |= square;
                }
            }
        }

        return bitboard;
    }
};

#endif // GAMEMODE_H












