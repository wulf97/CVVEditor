#ifndef VIDEOSEQ_H
#define VIDEOSEQ_H

#include <QObject>
#include <QImage>
#include <QString>
#include <QList>
#include <QTimer>

#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

#include "VideoSeqItem.h"

using namespace cv;

class Core;
class VideoLoader;

class VideoSeq : public QObject {
    Q_OBJECT
public:
    VideoSeq(QObject *parent = nullptr);

    void setConnection();
public slots:
    void clearSeq();
    void addToSeq(QString, int, int);
    void loadSeq();
    void unloadSeq();
    void saveSeq(QString);

    void seqUploadVideo(int);
    void seqWriteVideo();
    void seqPlayVideo();
    void seqPauseVideo();
    void seqStopVideo();
    void seqSetTime(int);
signals:
    void updateFrame(QImage*);
    void updateTime(int);
    void updateProgress(int);
    void isUploaded();
    void isPlayed();
    void isPaused();
    void isStoped();
private slots:
    void updateDisplayedFrame();
    void updateWritedFrame();
private:
    enum STATE {
        IS_PLAYED,
        IS_PAUSED,
        IS_STOPED
    };
private:
    Core *m_parent;
    VideoLoader *m_vLoader;
    QTimer m_displayTimer;
    QTimer m_saveTimer;
    QList<VideoSeqItem*> m_seq;
    VideoCapture m_inVideo;
    VideoWriter m_outVideo;
    QImage *m_frame = nullptr;
    int m_state = STATE::IS_STOPED;
    int m_it = 0;
    int m_fps = 0;
    int m_pos = 0;
    int m_time = 0;
};

#endif // VIDEOSEQ_H
