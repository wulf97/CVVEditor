#ifndef VIDEOCUTTERLIST_H
#define VIDEOCUTTERLIST_H

#include <QWidget>
#include <QVBoxLayout>

#include "VideoCutter.h"

namespace Ui {
class VideoCutterList;
}

class VideoCutterList : public QWidget {
    Q_OBJECT

public:
    explicit VideoCutterList(QWidget *parent = nullptr);
    ~VideoCutterList();

signals:
    void uploadVideo(QString*, bool);
    void unloadVideo();
    void stopVideo();
    void setStartTime(int);
    void setEndTime(int);
    void setMaxValueToSlider(int length);
    void sendLengthOfVideo(int);//отправка длины видео для VideoControlBar
    void sendCurrentPositionSlider(int);
    void clearSeq();
    void addToSeq(QString,int,int);
    void loadSeq();
public slots:
    void getVideoFilePath();
    void videoLen(int);
    void onCheckBoxStateChanged(int);
    bool move(QWidget *widget, QString direction);
    void sendCurrentTimeToCutter(int);
    void deleteVideoCutter(int);
private:
    void addNewCutter(QString*,int);
    Ui::VideoCutterList *ui;
    int countOfVideo;
    int m_length;
    QVBoxLayout *layout = new QVBoxLayout();
    QList<VideoCutter*> listOfVideoCutterWidgets;
    QString videoFilePath = nullptr;
    QString fileName = nullptr;
};

#endif // VIDEOCUTTERLIST_H
