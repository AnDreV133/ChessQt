#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QKeyEvent>
#include <QWidget>

namespace Ui {
class MenuWindow;
}

class MenuWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_btnPlay_clicked();

    void on_btnSettings_clicked();

private:
    Ui::MenuWindow *ui;
};

#endif // MENUWINDOW_H
