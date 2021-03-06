#include <QDebug>
#include <QLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "GUIManager.h"

#include "VideoCutterList.h"
#include "ui_VideoCutterList.h"

VideoCutterList::VideoCutterList(QWidget *parent) :
                                 QWidget(parent),
                                 ui(new Ui::VideoCutterList) {
    ui->setupUi(this);
    countOfVideo = 0;
    m_parent = dynamic_cast<GUIManager*>(parent);
    connect(this,SIGNAL(updateEffectRangeTime(int)),m_parent->getEffectRangeList(),SLOT(updateEndTime(int)));
}

VideoCutterList::~VideoCutterList() {
    delete ui;
}

int VideoCutterList::getLengthFullVideo()
{
    int endTime = 0;
    for (auto i : listOfVideoCutterWidgets) {
        VideoCutter* p = dynamic_cast<VideoCutter*>(i);
        endTime += (p->getMaximumValue() - p->getMinimumValue());
    }
    return endTime;
}

void VideoCutterList::getVideoFilePath() {
    videoFilePath = QFileDialog::getOpenFileName(this, tr("Open File"), "/",
                                                 tr("Video (*.avi *.mpeg *.mp4 *mkv)"));
    QFile mfile(videoFilePath);
    QString path = mfile.fileName();
    fileName = path.section("/",-1,-1);
    if (m_isSeqLoad) {
        m_isSeqLoad = false;
        emit unloadSeq();
    }
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

    addNewCutter(&lengthOfFilm, length);
    emit stopVideo();
    emit setEndTime(length);
    emit setMaxValueToSlider(length);
    emit updateEffectRangeTime(getLengthFullVideo());

}

void VideoCutterList::onCheckBoxStateChanged(int number) {
    bool checkALLCheckBox = false;

    for (auto i : listOfVideoCutterWidgets) {
        VideoCutter *p = dynamic_cast<VideoCutter*>(i);
        if (number != 0) {
            if (number != p->getNumberInListValue()) {
                p->setCheckBoxValue(false);
                qDebug() << "num: " << "num: " << p->getNumberInListValue();
                emit stopVideo();
            }

            checkALLCheckBox = true;
        }

        if (p->getCheckBoxValue() == true) {
            checkALLCheckBox = true;
        }
    }

    if (!checkALLCheckBox) {
        int endTime = 0;

        emit clearSeq();
        for (auto i : listOfVideoCutterWidgets) {
            VideoCutter* p = dynamic_cast<VideoCutter*>(i);
            endTime += (p->getMaximumValue() - p->getMinimumValue());
            emit addToSeq(*(p->getVideoFilePath()), p->getMinimumValue(), p->getMaximumValue());
        }

        m_isSeqLoad = true;

        emit loadSeq();
        emit setStartTime(0);
        emit setEndTime(endTime);
    } else {
        if (m_isSeqLoad) {
            m_isSeqLoad = false;
            emit unloadSeq();
        }
    }

}

void VideoCutterList::addNewCutter(QString *lengthOfFilm, int time) {
    if(lengthOfFilm) {
        countOfVideo++;
        VideoCutter* m_VideoCutter = new VideoCutter(this, countOfVideo, *lengthOfFilm, m_length, videoFilePath);
        m_VideoCutter->setNumberLabel(QString::number(countOfVideo));
        m_VideoCutter->setNumberInListValue(countOfVideo);
        m_VideoCutter->setNameOfFile(fileName);
        m_VideoCutter->setLenghtOfVideo(time);
        emit setStartTime(0);

        listOfVideoCutterWidgets.append(m_VideoCutter);
        m_VideoCutter->setCheckBoxValue(true);
        /* Делаем чекбоксы не активными */
        for (int i = 0; i < listOfVideoCutterWidgets.size() - 1; i++) {
            listOfVideoCutterWidgets[i]->setCheckBoxValue(false);
        }

        connect(m_VideoCutter, SIGNAL(checkBoxStateChanged(int)), this, SLOT(onCheckBoxStateChanged(int)));
        connect(m_VideoCutter, SIGNAL(uploadVideo(QString*, bool)), this, SIGNAL(uploadVideo(QString*, bool)));
        connect(m_VideoCutter, SIGNAL(upBtn(QWidget*,QString)), this, SLOT(move(QWidget*,QString)));
        connect(m_VideoCutter, SIGNAL(downBtn(QWidget*,QString)), this, SLOT(move(QWidget*,QString)));
        connect(m_VideoCutter, SIGNAL(sendLengthOfVideo(int)), this, SIGNAL(sendLengthOfVideo(int)));
        connect(m_VideoCutter, SIGNAL(sendCurrentPositionSlider(int)), this, SIGNAL(sendCurrentPositionSlider(int)));
        connect(m_VideoCutter, SIGNAL(sendNumberToDelete(int)), this, SLOT(deleteVideoCutter(int)));

        layout->addWidget(m_VideoCutter);
        this->setLayout(layout);
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

    for (auto i : listOfVideoCutterWidgets) {
        VideoCutter* p = dynamic_cast<VideoCutter*>(i);
        if(p->getNumberInListValue() != myLayout->indexOf(p) + 1) {
            p->setNumberInListValue(myLayout->indexOf(p) + 1);
            p->setNumberLabel(QString::number(myLayout->indexOf(p) + 1));
        }
    }

    return true;
}

void VideoCutterList::sendCurrentTimeToCutter(int time)
{
    for(auto i : listOfVideoCutterWidgets) {
        VideoCutter* p = dynamic_cast<VideoCutter*>(i);
        if(p->getValueOfCheckBox()) {
            p->rememberCurrentTimeOfVideo(time);
        }
    }

}

void VideoCutterList::deleteVideoCutter(int number)
{
    for(auto i : listOfVideoCutterWidgets) {
        VideoCutter* p = dynamic_cast<VideoCutter*>(i);
        if(p->getNumberInListValue() == number) {
            if(p->getCheckBoxValue()) {
                QMessageBox messageBox;
                messageBox.critical(0,"Ошибка","Невозможно удалить данное видео (уберите галочку)");
                messageBox.setFixedSize(500,200);
            } else {
                delete p;
                listOfVideoCutterWidgets.removeOne(p);
                countOfVideo--;

                emit stopVideo();
                if (listOfVideoCutterWidgets.isEmpty()) {
                    emit unloadVideo();
                } else {
                    emit uploadVideo(listOfVideoCutterWidgets[0]->getVideoFilePath(), false);
                }
            }
        }
    }

    if(!listOfVideoCutterWidgets.empty()){
        if(listOfVideoCutterWidgets[0]->getNumberInListValue() != 1){
            listOfVideoCutterWidgets[0]->setNumberInListValue(1);
            listOfVideoCutterWidgets[0]->setNumberLabel("1");
        }
        for (int i = 0; i < listOfVideoCutterWidgets.size(); i++) {
            if(i != 0){
                if((listOfVideoCutterWidgets[i]->getNumberInListValue() - listOfVideoCutterWidgets[i - 1]->getNumberInListValue()) != 1) {
                    listOfVideoCutterWidgets[i]->setNumberInListValue(listOfVideoCutterWidgets[i]->getNumberInListValue() - 1);
                    listOfVideoCutterWidgets[i]->setNumberLabel(QString::number(listOfVideoCutterWidgets[i]->getNumberInListValue()));
                }
            }
        }
    }


}

void VideoCutterList::saveFileAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save video"), "",
            tr(" avi (*.avi);;mpeg (*.mpeg);;mp4 (*.mp4);;mkv (*.mkv)"));
    emit clearSeq();
    for (auto i : listOfVideoCutterWidgets) {
        VideoCutter* p = dynamic_cast<VideoCutter*>(i);
        emit addToSeq(*(p->getVideoFilePath()), p->getMinimumValue(), p->getMaximumValue());
    }

    emit saveSeq(fileName);
}

void VideoCutterList::writeToJson()
{
    QJsonArray json;

    for (auto i : listOfVideoCutterWidgets) {
        VideoCutter* p = dynamic_cast<VideoCutter*>(i);
        auto data1 = QJsonObject({
                        qMakePair(QString("pathToVideo"),   QJsonValue(*p->getVideoFilePath())),
                        qMakePair(QString("nameOfFile"),    QJsonValue(p->getNameOfFile())),
                        qMakePair(QString("numberLabel"),   QJsonValue(p->getNumberInListValue())),
                        qMakePair(QString("checkBoxValue"), QJsonValue(p->getCheckBoxValue())),
                        qMakePair(QString("length"),        QJsonValue(p->getLengthOfVideo())),
                        qMakePair(QString("minValue"),      QJsonValue(p->getMinimumValue())),
                        qMakePair(QString("maxValue"),      QJsonValue(p->getMaximumValue())),
        });
        json.push_back(data1);

    }
    QJsonDocument doc(json);
    QDir appDir(qApp->applicationDirPath());
    QFile jsonfile(appDir.path() +"/file.json");
    jsonfile.open(QFile::WriteOnly);
    jsonfile.write(doc.toJson());
}

void VideoCutterList::writeToJsonAs()
{
    QString filePath = QFileDialog::getExistingDirectory(0, ("Select Output Folder"), QDir::currentPath());
    QJsonArray json;

    for (auto i : listOfVideoCutterWidgets) {
        VideoCutter* p = dynamic_cast<VideoCutter*>(i);
        auto data1 = QJsonObject({
                        qMakePair(QString("pathToVideo"),   QJsonValue(*p->getVideoFilePath())),
                        qMakePair(QString("nameOfFile"),    QJsonValue(p->getNameOfFile())),
                        qMakePair(QString("numberLabel"),   QJsonValue(p->getNumberInListValue())),
                        qMakePair(QString("checkBoxValue"), QJsonValue(p->getCheckBoxValue())),
                        qMakePair(QString("length"),        QJsonValue(p->getLengthOfVideo())),
                        qMakePair(QString("minValue"),      QJsonValue(p->getMinimumValue())),
                        qMakePair(QString("maxValue"),      QJsonValue(p->getMaximumValue())),
        });
        json.push_back(data1);

    }
    QJsonDocument doc (json);
    QFile jsonfile(filePath +"/mJson.json");
    jsonfile.open(QFile::WriteOnly);
    jsonfile.write(doc.toJson());
}

void VideoCutterList::readFromJson()
{
    emit unloadSeq();
    emit clearSeq();
    emit stopVideo();
    for (auto i : listOfVideoCutterWidgets) {
        VideoCutter* p = dynamic_cast<VideoCutter*>(i);
        delete p;
        listOfVideoCutterWidgets.removeOne(p);
        countOfVideo--;
    }

    QString jsonFilePath = QFileDialog::getOpenFileName(this, tr("Open Project"), "/",
                                                        tr("Project (*.json)"));
                                                        QFile jsonFile(jsonFilePath);
                                                        QByteArray loadData = jsonFile.readAll();

    QFile file(jsonFilePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2 = d.object();
    QJsonArray modulesArray = sett2[0].toArray();
    for (int moduleIndex = 0; moduleIndex < modulesArray.size(); ++moduleIndex) {
           QJsonObject moduleObject = modulesArray[moduleIndex].toObject();
       }
}
