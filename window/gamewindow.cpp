#include "chessscene.h"
#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "windialog.h"
#include "windowholder.h"

#include <QKeyEvent>

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
}

GameWindow::GameWindow(GameMode *gameMode, QWidget *parent)
    : GameWindow::GameWindow(parent) {
    ChessScene *chessScene = new ChessScene(640, gameMode, this);
    this->gameMode = gameMode;

    this->timePlayerOne = gameMode->timeLeftPlayerOne;
    this->timePlayerTwo = gameMode->timeLeftPlayerTwo;

    ui->graphicsView->setScene(chessScene);

    ui->tLabelTimerPlayerOne->setText(timerToString(timePlayerOne));
    ui->tLabelTimerPlayerTwo->setText(timerToString(timePlayerTwo));

    startTimerOne();

    connect(chessScene, SIGNAL(signalOtherTurn()), this, SLOT(switchTimer()));

    connect(&timerOne, SIGNAL(timeout()), this, SLOT(decrementTimeOne()));
    connect(&timerTwo, SIGNAL(timeout()), this, SLOT(decrementTimeTwo()));

    connect(chessScene, SIGNAL(signalNewLog(QString)), this, SLOT(postNewLog(QString)));
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        WindowHolder::holdPrevWidget();

        qDebug() << "escape pressed from" << this;
    }
}

void GameWindow::startTimerOne() {
    timerOne.start(1000);
}

void GameWindow::startTimerTwo() {
    timerTwo.start(1000);
}

void GameWindow::decrementTimeOne() {
    ui->tLabelTimerPlayerOne->setText(timerToString(timePlayerOne));
    timePlayerOne = timePlayerOne.addMSecs(-1000);

    if (timePlayerOne.hour() > 0) {
        WinDialog(2, this).show();
    }
}

void GameWindow::decrementTimeTwo() {
    ui->tLabelTimerPlayerTwo->setText(timerToString(timePlayerTwo));
    timePlayerTwo = timePlayerTwo.addMSecs(-1000);

    if (timePlayerOne.hour() > 0) {
        WinDialog(1, this).show();
    }
}

QString GameWindow::timerToString(QTime &time) {
    return QString(time.toString("mm : ss"));
}

void GameWindow::switchTimer() {
    qDebug() << "timer switched";

    if (timerOne.isActive()){
        timerOne.stop();
        timerTwo.start(1000);
    } else {
        timerTwo.stop();
        timerOne.start(1000);
    }

}

void GameWindow::postNewLog(QString event){
    ui->listWidget->addItem(event);
}

