#ifndef VIDEOSEQ_H
#define VIDEOSEQ_H

#include <QObject>
#include <QString>
#include <QList>

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

    void setConnect();
    void setDisconnect();
public slots:
    void addToSeq(QString, int, int);
    void clearSeq();
    void loadSeq();
    void unloadSeq();
    void saveSeq(QString);

    void seqUploadVideo(QString*, bool);
    void seqUnloadVideo();
    void seqPlayVideo();
    void seqStopVideo();
    void seqPauseVideo();
    void seqSetTime(int);
    void seqUpdateTime(int);
    void seqProgress(int);

    void nextVideoDisplay();
    void nextVideoWrite();
    void uploaded();
    void writeUploadedVideo();

signals:
    /* Сигналы идущие к VideoLoader */
    void uploadVideo(QString*, bool);
    void unloadVideo();
    void writeVideo(VideoWriter*);
    void playVideo();
    void stopVideo();
    void pauseVideo();
    void setTime(int);
    void setStartTime(int);
    void setEndTime(int);

    void updateTime(int);
    void stoped();
    void progress(int);
private:
    Core *m_parent = nullptr;
    VideoLoader *m_vLoader = nullptr;
    QList<VideoSeqItem*> m_seq;
    VideoWriter *m_outVideo = nullptr;
    int m_pos = 0;
    int m_time = 0;
    int m_iVideo = 0;
};

#endif // VIDEOSEQ_H
