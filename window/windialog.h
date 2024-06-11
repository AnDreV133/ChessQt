#ifndef WINDIALOG_H
#define WINDIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>

class WinDialog : public QDialog {
public:
    WinDialog(int numberOfWinner, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags()) : QDialog(parent, f) {
        QBoxLayout* layout = new QHBoxLayout(parent);
        QLabel *label = new QLabel(parent);
        label->setText(QString().append("Игрок ").append(QString::number(numberOfWinner).append("Одержал победу!")));
        layout->addWidget(label);
    }
};

#endif // WINDIALOG_H
