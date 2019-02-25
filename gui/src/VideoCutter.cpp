#include <QDebug>

#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>

#include "VideoCutter.h"
#include "ui_VideoCutter.h"
#include "RangeSlider.h"

VideoCutter::VideoCutter(QWidget *parent, int spinBoxValue, QString endTime, QString VideoFilePath) :
    QWidget(parent),
    ui(new Ui::VideoCutter) {
    ui->setupUi(this);
    videoFilePath = VideoFilePath;
    ui->spinBox->setValue(spinBoxValue);
    ui->endTime->setText(endTime);
}

VideoCutter::~VideoCutter() {
    delete ui;
}

QString* VideoCutter::getVideoFilePath()
{
    return &videoFilePath;
}

void VideoCutter::setSpinBoxValue(int value) {
    ui->spinBox->setValue(value);
}

void VideoCutter::setCheckBoxValue(bool value)
{
    ui->checkBox->setChecked(value);
}

int VideoCutter::getSpinBoxValue()
{
    return(ui->spinBox->value());
}

bool VideoCutter::getCheckBoxValue()
{
    return(ui->checkBox->isChecked());
}

void VideoCutter::on_checkBox_stateChanged(int arg1)
{
    if(getCheckBoxValue()){
    emit checkBoxStateChanged(getSpinBoxValue());
    emit uploadVideo(getVideoFilePath());
    }
}
