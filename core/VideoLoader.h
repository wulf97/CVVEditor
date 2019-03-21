#ifndef VIDEOLOADER_H
#define VIDEOLOADER_H

#include <QObject>
#include <QTimer>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

class Core;

class VideoLoader : public QObject {
    Q_OBJECT
public:
    VideoLoader(QObject *parent = nullptr);

    void setConnection();
public slots:
    void uploadVideo(QString*, bool);
    void unloadVideo();
    void playVideo();
    void pauseVideo();
    void stopVideo();
    void setTime(int);
    void setStartTime(int);
    void setEndTime(int);
signals:
    void videoLen(int);
    void updateFrame(QImage*);
    void updateTime(int);
    void isPlayed();
    void isPaused();
    void isStoped();
private slots:
    void updateDisplayedFrame();
private:
    Core *m_parent;
    VideoCapture m_video;
    VideoWriter *m_outVideo = nullptr;
    QTimer m_timer;
    bool m_isOpened = false;
    QString *m_path = nullptr;
    QImage *m_frame = nullptr;
    int m_fps = 0;
    int m_time = 0;
    int m_startTime = 0;
    int m_endTime = 0;
};

#endif // VIDEOLOADER_H
