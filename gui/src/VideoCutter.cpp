#include <QDebug>

#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>

#include "VideoCutter.h"
#include "ui_VideoCutter.h"
#include "RangeSlider.h"

VideoCutter::VideoCutter(QWidget *parent, int NumberInList, QString endTime, QString VideoFilePath) :
    QWidget(parent),
    ui(new Ui::VideoCutter) {
    ui->setupUi(this);
    videoFilePath = VideoFilePath;
    numberInList = NumberInList;
    ui->endTime->setText(endTime);
}

VideoCutter::~VideoCutter() {
    delete ui;
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

void VideoCutter::setNameOfFile(QString filename) {

    ui->nameOfFileLabel->setText(filename);
}



void VideoCutter::on_checkBox_stateChanged(int arg1) {
    if(getCheckBoxValue()) {
        emit checkBoxStateChanged(getNumberInListValue());
        emit uploadVideo(getVideoFilePath(), false);
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
