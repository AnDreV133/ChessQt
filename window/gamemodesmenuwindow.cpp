#include "gamemodesmenuwindow.h"
#include "ui_gamemodesmenuwindow.h"

#include "windowholder.h"
#include "gamewindow.h"
#include "../gamemode/pvspoffline.h"

GameModesMenuWindow::GameModesMenuWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameModesMenuWindow)
{
    ui->setupUi(this);
}

GameModesMenuWindow::~GameModesMenuWindow()
{
    delete ui;
}

void GameModesMenuWindow::on_btnPVsC_clicked()
{
    // todo in next updates
}


void GameModesMenuWindow::on_btnPVsPOfflane_clicked()
{
    WindowHolder::instance(new GameWindow(new PVsPOffline()))->show();
    qDebug("type P vs P offline showing");
}


void GameModesMenuWindow::on_btnPVsPOnline_clicked()
{
    // todo in next updates
}

void GameModesMenuWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        WindowHolder::holdPrevWidget();

        qDebug() << "escape pressed from" << this;
    }
}

