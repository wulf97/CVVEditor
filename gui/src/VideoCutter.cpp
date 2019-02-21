#include "VideoCutter.h"
#include "ui_VideoCutter.h"

VideoCutter::VideoCutter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoCutter) {
    ui->setupUi(this);
}

VideoCutter::~VideoCutter() {
    delete ui;
}

void VideoCutter::videoLen(int len) {

}
