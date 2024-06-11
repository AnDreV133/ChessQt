#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "windowholder.h"
#include "settingswindow.h"
#include "gamemodesmenuwindow.h"

#include <QMainWindow>
#include <QtLogging>

MenuWindow::MenuWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::on_btnPlay_clicked()
{
    WindowHolder::instance(new GameModesMenuWindow())->show();
    qDebug("game types showing");

}

void MenuWindow::on_btnSettings_clicked()
{
    WindowHolder::instance(new SettingsWindow())->show();
    qDebug("settings showing");
}

void MenuWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        WindowHolder::holdPrevWidget();
        WindowHolder::instance(this)->close();

        qDebug() << "escape pressed from" << this;
    }
}

