#include <QDebug>

#include "Viewport.h"
#include "ui_Viewport.h"

Viewport::Viewport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Viewport) {
    ui->setupUi(this);
}

Viewport::~Viewport() {
    delete ui;
}

void Viewport::updateFrame(QImage *img) {
    qDebug() << "slot: updateFrame(QImage*)" << endl;

    *img = img->scaledToWidth(ui->viewport->width());
    ui->viewport->setPixmap(QPixmap::fromImage(*img));
}
