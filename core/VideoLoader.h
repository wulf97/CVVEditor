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
    void writeVideo(VideoWriter*);
    void playVideo();
    void pauseVideo();
    void stopVideo();
    void setTime(int);
    void setStartTime(int);
    void setEndTime(int);
signals:
    void error(int);

    void videoLen(int);
    void uploaded();
    void updateFrame(QImage*);
    void isStoped();
    void updateTime(int);
    void ended();
private slots:
    void update();
    void updateWritedFrame();
private:
    Core *m_parent;
    VideoCapture m_video;
    VideoWriter *m_outVideo = nullptr;
    QTimer m_timer;
    QTimer m_timer2;
    /* Флаг для проверки открытия видео */
    bool m_isOpened = false;
    /* Путь к видео */
    QString *m_path = nullptr;
    /* Текущий кадр видео */
    QImage *m_frame = nullptr;
    /* Количество кадров в секунду */
    int m_fps = 0;
    /* Текущее время в миллисекундах */
    int m_time = 0;
    /* Начальное время фрагмента видео */
    int m_startTime = 0;
    /* Конечное время фрагмента видео */
    int m_endTime = 0;
};

#endif // VIDEOLOADER_H
