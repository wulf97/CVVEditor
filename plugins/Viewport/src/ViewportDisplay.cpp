#include "ViewportDisplay.h"

ViewportDisplay::ViewportDisplay(QWidget *parent) : QWidget(parent) {
    ui = new Ui::ViewportDisplay();
    ui->setupUi(this);
}

ViewportDisplay::~ViewportDisplay() {
    delete ui;
}

Ui::ViewportDisplay *ViewportDisplay::getUi() const {
    return ui;
}

void ViewportDisplay::resizeEvent(QResizeEvent *event) {
    emit windowResize();
}
