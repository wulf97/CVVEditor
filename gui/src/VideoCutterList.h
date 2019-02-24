#ifndef VIDEOCUTTERLIST_H
#define VIDEOCUTTERLIST_H

#include <QWidget>
#include <QVBoxLayout>

namespace Ui {
class VideoCutterList;
}

class VideoCutterList : public QWidget {
    Q_OBJECT

public:
    explicit VideoCutterList(QWidget *parent = nullptr);
    ~VideoCutterList();

signals:
    void uploadVideo(QString*);
public slots:
    void getVideoFilePath();
    void videoLen(int);
    void onCheckBoxStateChanged(int);
private:
    Ui::VideoCutterList *ui;
    int countOfVideo;
    QVBoxLayout *layout = new QVBoxLayout();
    QList <QWidget*> listOfVideoCutterVidgets;
};

#endif // VIDEOCUTTERLIST_H
