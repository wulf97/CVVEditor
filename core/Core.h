#ifndef CORE_H
#define CORE_H

#include <QObject>

#include "VideoLoader.h"
#include "VideoSeq.h"

class Core : public QObject {
    Q_OBJECT
public:
    Core(QObject *parent = nullptr);

    void testSignals();
signals:
    /* Сигналы для внутренних модулей */
    void uploadVideo(QString*, bool);
    void unloadVideo();
    void playVideo();
    void stopVideo();
    void pauseVideo();
    void setTime(int);
    void setStartTime(int);
    void setEndTime(int);
    void addToSeq(QString, int, int);
    void clearSeq();
    void loadSeq();

    /* Сигналы для внешних модулей */
    void videoLen(int);
    void updateFrame(QImage*);
    void stoped();
    void updateTime(int);
private:
    VideoLoader *m_VLoader = nullptr;
    VideoSeq *m_VSeq = nullptr;
};

#endif // CORE_H
