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
    QFile mfile(videoFilePath);
    QString path = mfile.fileName();
    fileName = path.section("/",-1,-1);
    emit uploadVideo(&videoFilePath, true);
}

void VideoCutterList::videoLen(int length) {
    int seconds;
    int minutes;
    int hours;
    m_length = length;
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

    addNewCutter(&lengthOfFilm);
    emit stopVideo();
    emit setEndTime(length);
    emit setMaxValueToSlider(length);

}

void VideoCutterList::onCheckBoxStateChanged(int number) {
    for(auto i : listOfVideoCutterWidgets) {
        VideoCutter* p = dynamic_cast<VideoCutter*>(i);
        if(number != p->getNumberInListValue()) {
            p->setCheckBoxValue(false);
            emit stopVideo();
        }
    }
}

void VideoCutterList::addNewCutter(QString *lengthOfFilm) {
    if(lengthOfFilm) {
        countOfVideo++;
        VideoCutter* m_VideoCutter = new VideoCutter(nullptr, countOfVideo, *lengthOfFilm, m_length, videoFilePath);
        m_VideoCutter->setNumberLabel(QString::number(countOfVideo));
        m_VideoCutter->setNumberInListValue(countOfVideo);
        m_VideoCutter->setCheckBoxValue(true);
        m_VideoCutter->setNameOfFile(fileName);
        /* Делаем чекбоксы не активными */
        for (int i = 0; i < listOfVideoCutterWidgets.size(); i++) {
            listOfVideoCutterWidgets[i]->setCheckBoxValue(false);
        }

        connect(m_VideoCutter, SIGNAL(checkBoxStateChanged(int)), this, SLOT(onCheckBoxStateChanged(int)));
        connect(m_VideoCutter, SIGNAL(uploadVideo(QString*, bool)), this, SIGNAL(uploadVideo(QString*, bool)));
        connect(m_VideoCutter, SIGNAL(upBtn(QWidget*,QString)), this, SLOT(move(QWidget*,QString)));
        connect(m_VideoCutter, SIGNAL(downBtn(QWidget*,QString)), this, SLOT(move(QWidget*,QString)));

        layout->addWidget(m_VideoCutter);
        this->setLayout(layout);
        listOfVideoCutterWidgets.append(m_VideoCutter);
    }
}

bool VideoCutterList::move(QWidget *widget, QString direction)
{
    QVBoxLayout* myLayout = qobject_cast<QVBoxLayout*>(widget->parentWidget()->layout());
    int index = myLayout->indexOf(widget);
    if (direction == "MoveUp" && index == 0) {
        return false;
    }

    if (direction == "MoveDown" && index == myLayout->count()-1 ) {
        return false;
    }

    int newIndex;
    if(direction == "MoveUp") {
         newIndex = index - 1;
    } else {
        newIndex = index + 1;
    }

    myLayout->removeWidget(widget);
    myLayout->insertWidget(newIndex , widget);

    for(auto i : listOfVideoCutterWidgets) {
        VideoCutter* p = dynamic_cast<VideoCutter*>(i);
        if(p->getNumberInListValue() != myLayout->indexOf(p) + 1) {
            p->setNumberInListValue(myLayout->indexOf(p) + 1);
            p->setNumberLabel(QString::number(myLayout->indexOf(p) + 1));
        }
    }

    return true;
}
