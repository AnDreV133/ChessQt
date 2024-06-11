#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QKeyEvent>
#include <QMainWindow>

#include "../settings/settingsjson.h"

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();

    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_btnSave_clicked();

    void on_btnSetFileNameToFigureDisposition_clicked();

    void on_rBtnClassicDisposition_clicked();

    void on_rBtnCustomDisposition_clicked();

private:
    Ui::SettingsWindow *ui;
};

#endif // SETTINGSWINDOW_H
