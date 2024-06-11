#ifndef PVSPOFFLINE_H
#define PVSPOFFLINE_H

#include "gamemode.h"

class PVsPOffline : public GameMode {
public:
    PVsPOffline() : GameMode() {
        if (settings.figureDisposition == FigureDisposition::CUSTOM)
            figurePlacement = convertFileFromSettingsToDisposition();
        else
            figurePlacement = convertStringToDisposition(classicDisposition);

        figureDispositionBitboard = convertDispositionToBitboard(figurePlacement);

        timeLeftPlayerOne = QTime(0, settings.minOnTimer, settings.secOnTimer);
        timeLeftPlayerTwo = QTime(0, settings.minOnTimer, settings.secOnTimer);
    }

    void switchTurn() override {
        if (turnColor == FigureColor::WHITE)
            turnColor = FigureColor::BLACK;
        else if (turnColor == FigureColor::BLACK)
            turnColor = FigureColor::WHITE;
    }
};

#endif // PVSPOFFLINE_H
