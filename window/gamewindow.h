#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include "../gamemode/gamemode.h"
#include "../gamemode/chesslogger.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    GameWindow(GameMode *gameMode, QWidget *parent = nullptr);
    ~GameWindow();
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::GameWindow *ui;
    QTimer timerOne;
    QTimer timerTwo;
    GameMode *gameMode;
    QTime timePlayerOne;
    QTime timePlayerTwo;

    QString timerToString(QTime &time);

private slots:
    void startTimerOne();
    void startTimerTwo();
    void decrementTimeOne();
    void decrementTimeTwo();
    void switchTimer();
    void postNewLog(QString event);
};

#endif // GAMEWINDOW_H
