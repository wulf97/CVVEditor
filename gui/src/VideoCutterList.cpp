#include <QDebug>
#include <QLayout>
#include <QPushButton>
#include <QFileDialog>

#include "VideoCutterList.h"
#include "ui_VideoCutterList.h"
#include "VideoCutter.h"

VideoCutterList::VideoCutterList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoCutterList) {
    ui->setupUi(this);
}

VideoCutterList::~VideoCutterList() {
    delete ui;
}

void VideoCutterList::getVideoFilePath() {
    QString videoFilePath = QFileDialog::getOpenFileName(this, tr("Open File"), "/",
                                                         tr("Video (*.avi *.mpeg *.mp4 *mkv)"));
    emit uploadVideo(&videoFilePath);
}

void VideoCutterList::videoLen(int length) {
    qDebug() << "leng: " << length << endl;
    //layout->addWidget(new VideoCutter(nullptr,countOfVideo,QString::number(length/60) +":"+QString::number(length - length/60)));
}
