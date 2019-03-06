#ifndef VIDEOSEQ_H
#define VIDEOSEQ_H

#include <QObject>
#include <QString>
#include <QList>

#include "VideoSeqItem.h"

class Core;

class VideoSeq : public QObject {
    Q_OBJECT
public:
    VideoSeq(QObject *parent = nullptr);
public slots:
    void addToSeq(QString, int, int);
    void clearSeq();
    void loadSeq();
    void unloadSeq();

    void seqUploadVideo(QString*, bool);
    void seqUnloadVideo();
    void seqPlayVideo();
    void seqStopVideo();
    void seqPauseVideo();
    void seqSetTime(int);
    void seqUpdateTime(int);

    void nextVideo();
    void uploaded();

signals:
    /* Сигналы идущие к VideoLoader */
    void uploadVideo(QString*, bool);
    void unloadVideo();
    void playVideo();
    void stopVideo();
    void pauseVideo();
    void setTime(int);
    void setStartTime(int);
    void setEndTime(int);

    void updateTime(int);
private:
    Core *m_core = nullptr;
    QList<VideoSeqItem*> m_seq;
    int m_pos = 0;
    int m_time = 0;
    int m_iVideo = 0;
};

#endif // VIDEOSEQ_H
