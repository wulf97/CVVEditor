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
public slots:
    void getVideoFilePath();
    void videoLen(int);
    void onCheckBoxStateChanged(int);
private:
    void addNewCutter(QString*);
    Ui::VideoCutterList *ui;
    int countOfVideo;
    QVBoxLayout *layout = new QVBoxLayout();
    QList<VideoCutter*> listOfVideoCutterWidgets;
    QString videoFilePath = nullptr;
};

#endif // VIDEOCUTTERLIST_H
