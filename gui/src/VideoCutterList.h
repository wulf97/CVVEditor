#ifndef VIDEOCUTTERLIST_H
#define VIDEOCUTTERLIST_H

#include <QWidget>
#include <QVBoxLayout>

#include "VideoCutter.h"

class GUIManager;
namespace Ui {
class VideoCutterList;
}

class VideoCutterList : public QWidget {
    Q_OBJECT

public:
    explicit VideoCutterList(QWidget *parent = nullptr);
    ~VideoCutterList();

    int getLengthFullVideo();
signals:
    void uploadVideo(QString*, bool);
    void unloadVideo();
    void stopVideo();
    void setStartTime(int);
    void setEndTime(int);
    void setMaxValueToSlider(int length);
    void sendLengthOfVideo(int);//отправка длины видео для VideoControlBar
    void sendCurrentPositionSlider(int);
    void addToSeq(QString, int, int);
    void clearSeq();
    void loadSeq();
    void unloadSeq();
    void saveSeq(QString);
    void updateEffectRangeTime(int);
public slots:
    void getVideoFilePath();
    void videoLen(int);
    void onCheckBoxStateChanged(int);
    bool move(QWidget *widget, QString direction);
    void sendCurrentTimeToCutter(int);
    void deleteVideoCutter(int);
    void saveFileAs();
    void writeToJson();
    void writeToJsonAs();
    void readFromJson();
private:
    GUIManager *m_parent;
    void addNewCutter(QString*,int);
    Ui::VideoCutterList *ui;
    int countOfVideo;
    int m_length;
    QVBoxLayout *layout = new QVBoxLayout();
    QList<VideoCutter*> listOfVideoCutterWidgets;
    QString videoFilePath = nullptr;
    QString fileName = nullptr;
    bool m_isSeqLoad = false;
};

#endif // VIDEOCUTTERLIST_H
