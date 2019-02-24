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
    if(length !=0){
        countOfVideo++;
        VideoCutter* m_VideoCutter = new VideoCutter(nullptr, countOfVideo, QString::number(length/60) + ":" + QString::number(length % 60));
        connect(m_VideoCutter, SIGNAL(checkBoxStateChanged(int)), this, SLOT(onCheckBoxStateChanged(int)));

        layout->addWidget(m_VideoCutter);
        if (countOfVideo == 1) {
            m_VideoCutter->setCheckBoxValue(true);
        }

        this->setLayout(layout);
        listOfVideoCutterVidgets.append(m_VideoCutter);
    }
}

void VideoCutterList::onCheckBoxStateChanged(int number) {
    for (auto i : listOfVideoCutterVidgets) {
        VideoCutter* p = dynamic_cast<VideoCutter*>(i);
        if (number != p->getSpinBoxValue()) {
            p->setCheckBoxValue(false);
        }
    }
}
