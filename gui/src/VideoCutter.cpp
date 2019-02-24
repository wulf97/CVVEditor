#include <QDebug>

#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>

#include "VideoCutter.h"
#include "ui_VideoCutter.h"
#include "RangeSlider.h"

VideoCutter::VideoCutter(QWidget *parent, int spinBoxValue, QString endTime) :
    QWidget(parent),
    ui(new Ui::VideoCutter) {
    ui->setupUi(this);
    this->setFixedHeight(40);
    ui->checkBox->setStyleSheet("QCheckBox::indicator { width:110px; height: 110px; }");
    ui->spinBox->setValue(spinBoxValue);
    ui->endTime->setText(endTime);
}

VideoCutter::~VideoCutter() {
    delete ui;
}


void VideoCutter::setSpinBoxValue(int value) {
    ui->spinBox->setValue(value);
}
