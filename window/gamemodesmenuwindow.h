#ifndef GAMEMODESMENUWINDOW_H
#define GAMEMODESMENUWINDOW_H

#include <QKeyEvent>
#include <QWidget>

namespace Ui {
class GameModesMenuWindow;
}

class GameModesMenuWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameModesMenuWindow(QWidget *parent = nullptr);
    ~GameModesMenuWindow();
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_btnPVsC_clicked();

    void on_btnPVsPOfflane_clicked();

    void on_btnPVsPOnline_clicked();

private:
    Ui::GameModesMenuWindow *ui;
};

#endif // GAMEMODESMENUWINDOW_H
