#include <QDebug>

#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>

#include "VideoCutter.h"
#include "ui_VideoCutter.h"
#include "RangeSlider.h"

VideoCutter::VideoCutter(QWidget *parent, int NumberInList, QString endTimeString, int endTimeNumber, QString VideoFilePath) :
                         QWidget(parent),
                         ui(new Ui::VideoCutter) {
    ui->setupUi(this);
    m_RangeSlider = new RangeSlider();
    ui->horizontalLayout_5->addWidget(m_RangeSlider);
    videoFilePath = VideoFilePath;
    numberInList = NumberInList;
    ui->endTime->setText(endTimeString);
    setMinimumValue(0);
    setMaximumValue(endTimeNumber);

    connect(m_RangeSlider,SIGNAL(lowerValueChanged(int)), this, SLOT(onLowerValueChanged(int)));
    connect(m_RangeSlider,SIGNAL(upperValueChanged(int)), this, SLOT(onUpperValueChanged(int)));
    connect(ui->deleteBtn, SIGNAL(released()), this, SLOT(deleteMe()));
    connect(this, SIGNAL(setStartTime(int)), parent, SIGNAL(setStartTime(int)));
    connect(this, SIGNAL(setEndTime(int)), parent, SIGNAL(setEndTime(int)));
}

VideoCutter::~VideoCutter() {
    delete ui;
}

void VideoCutter::setMaximumValue(int max)
{
    m_RangeSlider->setMaximum(max);
    upperValue = max;
    setCheckBoxValue(true);
}

int VideoCutter::getMaximumValue()
{
    return upperValue;
}

void VideoCutter::setMinimumValue(int min)
{
    m_RangeSlider->setMinimum(min);
    setCheckBoxValue(true);
}

int VideoCutter::getMinimumValue()
{
    return lowerValue;
}


void VideoCutter::setNumberInListValue(int number)
{
    numberInList = number;
}

void VideoCutter::setCheckBoxValue(bool value) {
    ui->checkBox->setChecked(value);
}

int VideoCutter::getNumberInListValue()
{
    return numberInList;
}

bool VideoCutter::getCheckBoxValue() {
    return(ui->checkBox->isChecked());
}

void VideoCutter::setNumberLabel(QString number)
{
    QFont font = ui->numberLabel->font();
    font.setPointSize(12);
    font.setBold(true);
    ui->numberLabel->setFont(font);
    ui->numberLabel->setText(number);
}

QString* VideoCutter::getVideoFilePath() {

    return &videoFilePath;
}

int VideoCutter::getLengthOfVideo()
{
    return lengthOfFilm;
}

void VideoCutter::setNameOfFile(QString mfilename) {

    filename = mfilename;
    ui->nameOfFileLabel->setText(filename);
}

QString VideoCutter::getNameOfFile()
{
    return filename;
}

void VideoCutter::setLenghtOfVideo(int length)
{
    lengthOfFilm = length;
}

bool VideoCutter::getValueOfCheckBox()
{
    return ui->checkBox->isChecked();
}

QString VideoCutter::videoLen(int length)
{
    int seconds;
    int minutes;
    int hours;

    QString second;
    QString minute;
    QString hour;
    QString lengthOfFilm;

    seconds = (length/1000)%60;
    minutes = ((length/1000)/60)%60;
    hours = ((length/1000)/60)/60;
    if(QString::number(seconds).length() == 1) {
        second = "0" + QString::number(seconds);
    } else {
        second = QString::number(seconds);
    }

    if(QString::number(minutes).length() == 1) {
        minute = "0" + QString::number(minutes);
    } else {
        minute = QString::number(minutes);
    }

    if(QString::number(hours).length() == 1) {
        hour = "0" + QString::number(hours);
    } else {
        hour = QString::number(hours);
    }

    if (hours == 0) {
        if (minutes == 0){
            lengthOfFilm = "00:00:" + second;
        } else {
            lengthOfFilm = "00:" + minute + ':' + second;
        }
    } else {
        lengthOfFilm = hour +':' + minute + ':' + second;
    }

    return lengthOfFilm;

}

void VideoCutter::onLowerValueChanged(int aLowerValue)
{
    qDebug() << "Min: " << lowerValue;
    lowerValue = aLowerValue;
    ui->startTime->setText(videoLen(aLowerValue));
    if(getValueOfCheckBox()) {
        emit setStartTime(aLowerValue);
    }


}

void VideoCutter::onUpperValueChanged(int aUpperValue)
{
    qDebug() << "Max: " << upperValue;
    upperValue = aUpperValue;
    ui->endTime->setText(videoLen(aUpperValue));
    if(getValueOfCheckBox()) {
        emit setEndTime(aUpperValue);
    }
}

void VideoCutter::rememberCurrentTimeOfVideo(int time)
{
    currentTimeInControlBar = time;
}


void VideoCutter::on_checkBox_stateChanged(int arg1) {
    if (getCheckBoxValue()) {
        emit uploadVideo(getVideoFilePath(), false);
        emit sendLengthOfVideo(lengthOfFilm);
        emit sendCurrentPositionSlider(currentTimeInControlBar);
        emit setStartTime(lowerValue);
        emit setEndTime(upperValue);
        emit checkBoxStateChanged(getNumberInListValue());
    } else {
        emit checkBoxStateChanged(0);
    }
}

void VideoCutter::on_upBtn_clicked()
{
    emit upBtn(this,"MoveUp");
}

void VideoCutter::on_downBtn_clicked()
{
    emit downBtn(this,"MoveDown");
}

void VideoCutter::deleteMe()
{
    emit (sendNumberToDelete(getNumberInListValue()));
}
