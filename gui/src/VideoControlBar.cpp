#include <QDebug>

#include "VideoControlBar.h"
#include "ui_VideoControlBar.h"

VideoControlBar::VideoControlBar(QWidget *parent) :
                                 QWidget(parent),
                                 ui(new Ui::VideoControlBar) {
    ui->setupUi(this);

    ui->play->setDisabled(true);
    ui->pause->setDisabled(true);
    ui->stop->setDisabled(true);

    connect(ui->play, SIGNAL(released()), this, SIGNAL(playVideo()));
    connect(ui->pause, SIGNAL(released()), this, SIGNAL(pauseVideo()));
    connect(ui->stop, SIGNAL(released()), this, SIGNAL(stopVideo()));
    connect(ui->add, SIGNAL(released()), this, SIGNAL(getVideoFilePath()));
    connect(ui->slider, SIGNAL(sliderMoved(int)), this, SLOT(sliderMove(int)));

    connect(this, SIGNAL(playVideo()), this, SLOT(play()));
    connect(this, SIGNAL(pauseVideo()), this, SLOT(pause()));
    connect(this, SIGNAL(stopVideo()), this, SLOT(stop()));

    ui->slider->setValue(0);
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

void VideoControlBar::setSliderPosition(int currenTime) {
    ui->slider->setValue(currenTime);
}

void VideoControlBar::play() {
    ui->play->setDisabled(true);
    ui->pause->setEnabled(true);
    ui->stop->setEnabled(true);
}

void VideoControlBar::pause() {
    ui->play->setEnabled(true);
    ui->pause->setDisabled(true);
}

void VideoControlBar::stop() {
    ui->play->setEnabled(true);
    ui->pause->setDisabled(true);
    ui->stop->setDisabled(true);
}

void VideoControlBar::stoped() {
    qDebug() << "slot: stoped()" << endl;
}

void VideoControlBar::setStartTime(int time) {
    qDebug() << "slot: setStartTime(int)" << endl;

    m_startTime = time;
    setSliderMaxValue(m_endTime - m_startTime);
}

void VideoControlBar::setEndTime(int time) {
    qDebug() << "slot: setEndTime(int)" << endl;

    m_endTime = time;
    ui->endTime->setText(msecToTime(time - m_startTime));
    setSliderMaxValue(m_endTime - m_startTime);
}

void VideoControlBar::updateTime(int time) {
    int endTime = m_endTime - time;

    setSliderPosition(time);
    ui->startTime->setText(msecToTime(time));
    ui->endTime->setText(msecToTime(endTime));
}

void VideoControlBar::setSliderMaxValue(int) {
    ui->slider->setMaximum(m_endTime);
}


void VideoControlBar::slotSetSliderPosition(int time)
{
    setTime(time);
    setSliderPosition(time);
}

/* Перевод мсек во время ЧЧ:ММ:СС */
QString VideoControlBar::msecToTime(int time) {
    int seconds;
    int minuts;
    int hours;

    QString second;
    QString minute;
    QString hour;
    QString lengthOfFilm;

    seconds = (time/1000)%60;
    minuts = ((time/1000)/60)%60;
    hours = ((time/1000)/60)/60;

    if(QString::number(seconds).length() == 1) {
        second = "0" + QString::number(seconds);
    } else {
        second = QString::number(seconds);
    }

    if(QString::number(minuts).length() == 1) {
        minute = "0" + QString::number(minuts);
    } else {
        minute = QString::number(minuts);
    }

    if(QString::number(hours).length() == 1) {
        hour = "0" + QString::number(hours);
    } else {
        hour = QString::number(hours);
    }

    if (hours == 0) {
        if (minuts == 0){
            lengthOfFilm = "00:00:" + second;
        } else {
            lengthOfFilm = "00:" + minute + ':' + second;
        }
    } else {
        lengthOfFilm = hour +':' + minute + ':' + second;
    }

    return lengthOfFilm;
}

void VideoControlBar::sliderMove(int value) {
    emit setTime(value);
    emit sendTime (value);
}

