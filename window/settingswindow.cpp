#include "settingswindow.h"
#include "ui_settingswindow.h"
#include "windowholder.h"

#include <string>
#include <QFileDialog>
#include <QErrorMessage>

#include "../utils.h"

SettingsWindow::SettingsWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SettingsWindow) {
    ui->setupUi(this);

    SettingsJson settingsJson;
    if (SettingsJson::updateParametresFromJsonFile(settingsJson))
        qDebug() << "update parametres success";
    else {
        qDebug() << "update not completed";
        (new QErrorMessage(this))->showMessage(QString("Получить настройки не удалось!"));
    }

    switch (settingsJson.colorFigureInBottom){
        case FigureColor::WHITE:
            ui->rBtnDownLocateWhite->setChecked(true);
            break;

        case FigureColor::BLACK:
            ui->rBtnDownLocateBlack->setChecked(true);
            break;

        case FigureColor::DEFAULT:
            ui->rBtnDownLocateDefault->setChecked(true);
            break;
    }

    ui->lEditMinOnTimer->setText(QString::number(settingsJson.minOnTimer));
    ui->lEditSecOnTimer->setText(QString::number(settingsJson.secOnTimer));

    switch (settingsJson.figureDisposition){
    case FigureDisposition::CLASSIC:
        on_rBtnClassicDisposition_clicked();
        break;

    case FigureColor::BLACK:
        on_rBtnCustomDisposition_clicked();
        break;
    }

    ui->lEditFileNameToFigureDisposition->setText(Utils::toQString(settingsJson.fileNameOfFigureDisposition));
}

SettingsWindow::~SettingsWindow() {
    delete ui;
}

void SettingsWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        WindowHolder::holdPrevWidget();

        qDebug() << "escape pressed from" << this;
    }
}

void SettingsWindow::on_btnSave_clicked() {
    SettingsJson settingsJson;
    if (ui->rBtnDownLocateWhite->isChecked())
        settingsJson.colorFigureInBottom = FigureColor::WHITE;
    else if (ui->rBtnDownLocateBlack->isChecked())
        settingsJson.colorFigureInBottom = FigureColor::BLACK;
    else if (ui->rBtnDownLocateDefault->isChecked())
        settingsJson.colorFigureInBottom = FigureColor::DEFAULT;

    int minutes = ui->lEditMinOnTimer->text().toInt();
    if (minutes < 0 || minutes > 150)
        ui->lEditMinOnTimer->setText(Utils::toCharArr(settingsJson.minOnTimer));
    else
        settingsJson.minOnTimer = minutes;

    int second = ui->lEditSecOnTimer->text().toInt();
    if (second < 0 || second > 59)
        ui->lEditSecOnTimer->setText(Utils::toCharArr(settingsJson.secOnTimer));
    else
        settingsJson.secOnTimer = second;

    if (ui->rBtnClassicDisposition->isChecked())
        settingsJson.figureDisposition = FigureDisposition::CLASSIC;
    else if (ui->rBtnCustomDisposition->isChecked())
        settingsJson.figureDisposition = FigureDisposition::CUSTOM;

    settingsJson.fileNameOfFigureDisposition = ui->lEditFileNameToFigureDisposition->text().toStdString();

    if (SettingsJson::saveParametresToJsonFile(settingsJson))
        qDebug() << "save correctly";
    else
        qDebug() << "not saved";
}


void SettingsWindow::on_btnSetFileNameToFigureDisposition_clicked()
{
    ui->lEditFileNameToFigureDisposition->setText(
        QFileDialog::getOpenFileName(
            this,
            QString(),
            QString(),
            "txt (*.txt)")
        );
}


void SettingsWindow::on_rBtnClassicDisposition_clicked()
{
    ui->rBtnClassicDisposition->setChecked(true);
    ui->lEditFileNameToFigureDisposition->setDisabled(true);
    ui->btnSetFileNameToFigureDisposition->setDisabled(true);
}


void SettingsWindow::on_rBtnCustomDisposition_clicked()
{
    ui->rBtnCustomDisposition->setChecked(true);
    ui->lEditFileNameToFigureDisposition->setEnabled(true);
    ui->btnSetFileNameToFigureDisposition->setEnabled(true);
}

