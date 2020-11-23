#ifndef VIEWPORT_DISPLAY_H
#define VIEWPORT_DISPLAY_H

#include <QWidget>

#include "ui_ViewportDisplay.h"

namespace Ui {
class ViewportDisplay;
}

class ViewportDisplay : public QWidget {
    Q_OBJECT
public:
    ViewportDisplay(QWidget *parent = nullptr);
    ~ViewportDisplay();

    Ui::ViewportDisplay *getUi() const;

private:
    void resizeEvent(QResizeEvent *event);

signals:
    void windowResize();
private:
    Ui::ViewportDisplay *ui;
};

#endif // VIEWPORT_DISPLAY_H
