#include <QDebug>
#include <QLayout>
#include <QPushButton>
#include <QFileDialog>

#include "VideoCutterList.h"
#include "ui_VideoCutterList.h"

VideoCutterList::VideoCutterList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoCutterList) {
    ui->setupUi(this);
    countOfVideo = 0;
}

VideoCutterList::~VideoCutterList() {
    delete ui;
}

void VideoCutterList::getVideoFilePath() {
    videoFilePath = QFileDialog::getOpenFileName(this, tr("Open File"), "/",
                                                 tr("Video (*.avi *.mpeg *.mp4 *mkv)"));
    emit uploadVideo(&videoFilePath, true);
}

void VideoCutterList::videoLen(int length) {
    QString lengthOfFilm;
    int seconds = 0;
    int minutes = length/60000;
    int hours = 0;
    QString second, minute, hour;
    if (minutes == 0) {
        seconds = length/1000;
    }
    else {
        if (minutes > 60) {
            hours = minutes/60;
            minutes = minutes%60;
        }

        seconds = minutes%60;
    }

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

    addNewCutter(&lengthOfFilm);
}

void VideoCutterList::onCheckBoxStateChanged(int number) {
    for(auto i : listOfVideoCutterWidgets) {
        VideoCutter* p = dynamic_cast<VideoCutter*>(i);
        if(number != p->getSpinBoxValue()) {
            p->setCheckBoxValue(false);
        }
    }
}

void VideoCutterList::addNewCutter(QString *lengthOfFilm) {
    if(lengthOfFilm) {
        countOfVideo++;
        VideoCutter* m_VideoCutter = new VideoCutter(nullptr, countOfVideo, *lengthOfFilm, videoFilePath);

        m_VideoCutter->setCheckBoxValue(true);
        /* Делаем чекбоксы не активными */
        for (int i = 0; i < listOfVideoCutterWidgets.size(); i++) {
            listOfVideoCutterWidgets[i]->setCheckBoxValue(false);
        }

        connect(m_VideoCutter, SIGNAL(checkBoxStateChanged(int)), this, SLOT(onCheckBoxStateChanged(int)));
        connect(m_VideoCutter, SIGNAL(uploadVideo(QString*, bool)), this, SIGNAL(uploadVideo(QString*, bool)));

        layout->addWidget(m_VideoCutter);

        this->setLayout(layout);
        listOfVideoCutterWidgets.append(m_VideoCutter);
    }
}
