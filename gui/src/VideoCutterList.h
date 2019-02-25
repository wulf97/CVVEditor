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
    void sendNameOfFile(QString);
    void setStartTime(int);
    void setEndTime(int);
public slots:
    void getVideoFilePath();
    void videoLen(int);
    void onCheckBoxStateChanged(int);
    bool move(QWidget *widget, QString direction);
private:
    void addNewCutter(QString*);
    Ui::VideoCutterList *ui;
    int countOfVideo;
    QVBoxLayout *layout = new QVBoxLayout();
    QList<VideoCutter*> listOfVideoCutterWidgets;
    QString videoFilePath = nullptr;
    QString fileName = nullptr;
};

#endif // VIDEOCUTTERLIST_H
