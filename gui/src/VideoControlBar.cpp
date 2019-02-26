#include <QDebug>

#include "VideoControlBar.h"
#include "ui_VideoControlBar.h"

VideoControlBar::VideoControlBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoControlBar) {
    ui->setupUi(this);

    ui->pause->setDisabled(true);

    connect(ui->play, SIGNAL(released()), this, SIGNAL(playVideo()));
    connect(ui->pause, SIGNAL(released()), this, SIGNAL(pauseVideo()));
    connect(ui->stop, SIGNAL(released()), this, SIGNAL(stopVideo()));
    connect(ui->add, SIGNAL(released()), this, SIGNAL(getVideoFilePath()));

    connect(ui->play, SIGNAL(released()), this, SLOT(play()));
    connect(ui->pause, SIGNAL(released()), this, SLOT(pause()));
    connect(ui->stop, SIGNAL(released()), this, SLOT(stop()));
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

void VideoControlBar::play() {
    ui->play->setDisabled(true);
    ui->pause->setEnabled(true);
}

void VideoControlBar::pause() {
    ui->play->setEnabled(true);
    ui->pause->setDisabled(true);
}

void VideoControlBar::stop() {
    ui->play->setEnabled(true);
    ui->pause->setDisabled(true);
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

    ui->endTime->setText(msecToTime(time - m_startTime));
}

void VideoControlBar::updateTime(int time) {
    ui->startTime->setText(msecToTime(time));
}

/* Перевод мсек во время ЧЧ:ММ:СС */
QString VideoControlBar::msecToTime(int time) {
    int seconds;
    int minuts;
    int hours;

    seconds = (time/1000)%60;
    minuts = ((time/1000)/60)%60;
    hours = ((time/1000)/60)/60;

    return QString("%1:%2:%3").arg(hours).arg(minuts).arg(seconds);
}
