#include <QDebug>

#include "VideoControlBar.h"
#include "ui_VideoControlBar.h"

VideoControlBar::VideoControlBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoControlBar) {
    ui->setupUi(this);
}

VideoControlBar::~VideoControlBar() {
    delete ui;
}

void VideoControlBar::stoped() {
    qDebug() << "slot: stoped()" << endl;
}
