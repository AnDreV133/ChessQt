#ifndef WINDOWHOLDER_H
#define WINDOWHOLDER_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QDebug>
#include <QStackedWidget>

namespace Ui {
class WindowHolder;
}

class WindowHolder
{
public:
    static QMainWindow* instance(QWidget *widget) {
        if (!windowHolder) {
            windowHolder = new QMainWindow();
            windowHolder->setWindowTitle("Kill King!");
            windowHolder->resize(400, 300);
            widget->setFocus();

            widgetStack = new QStackedWidget();
        }

        if (widget != nullptr) {
            widgetStack->addWidget(widget);
            widgetStack->setCurrentWidget(widget);
            windowHolder->setCentralWidget(widgetStack);

            qDebug() << "widget:" << widget << "is holded";
        }

        return windowHolder;
    }

    static void holdPrevWidget() {
        if(widgetStack == nullptr) {
            qDebug() << "widgetStack is null";
            return;
        }

        if (widgetStack->count()) {
            widgetStack->removeWidget(widgetStack->currentWidget());
        }

        if (widgetStack->count()) {
            windowHolder->setCentralWidget(widgetStack);
        }

        qDebug() << "hold prev widget, back to" << widgetStack->currentWidget();
    }

private:
    Ui::WindowHolder *ui;
    WindowHolder() {}
    ~WindowHolder() {}

    inline static QMainWindow *windowHolder = nullptr;
    inline static QStackedWidget *widgetStack = nullptr;

    WindowHolder(WindowHolder const&);
    WindowHolder& operator= (WindowHolder const&);
};

#endif // WINDOWHOLDER_H
