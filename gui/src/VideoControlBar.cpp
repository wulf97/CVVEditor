#include <QDebug>

#include "VideoControlBar.h"
#include "ui_VideoControlBar.h"

VideoControlBar::VideoControlBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoControlBar) {
    ui->setupUi(this);

    connect(ui->play, SIGNAL(released()), this, SIGNAL(playVideo()));
    connect(ui->pause, SIGNAL(released()), this, SIGNAL(pauseVideo()));
    connect(ui->stop, SIGNAL(released()), this, SIGNAL(stopVideo()));
    connect(ui->add, SIGNAL(released()), this, SIGNAL(getVideoFilePath()));

}

VideoControlBar::~VideoControlBar() {
    delete ui;
}

/* Функция для тестирование работы сигналов */
void VideoControlBar::testSignals() {
    qDebug() << "Response on VideoControlBar signals:" << endl;
    qDebug() << "***" << endl;
    emit playVideo();
    emit stopVideo();
    emit pauseVideo();
    qDebug() << "***" << endl;
}

void VideoControlBar::stoped() {
    qDebug() << "slot: stoped()" << endl;
}

void VideoControlBar::setStartTime(int time) {
    qDebug() << "slot: setStartTime(int)" << endl;

    m_startTime = time;
}

void VideoControlBar::setEndTime(int time) {
    qDebug() << "slot: setEndTime(int)" << endl;

    m_endTime = time;
}
