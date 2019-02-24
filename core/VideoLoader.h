#ifndef VIDEOLOADER_H
#define VIDEOLOADER_H

#include <QObject>
#include <QTimer>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

class VideoLoader : public QObject {
    Q_OBJECT
public:
    VideoLoader(QObject *parent = nullptr);

    void testSignals();
public slots:
    /* Загрузить видео */
    void uploadVideo(QString*);
    /* Начать отправку кадров */
    void playVideo();
    /* Останавливить отправку кадров и сбрасить счетчик кадров */
    void stopVideo();
    /* Приостанавить отправку кадров */
    void pauseVideo();
    /* Установить начальный кадр */
    /* Установить конечный кадр */
signals:
    /* Метод для отлавливания ошибок */
    void error(int);

    /* Передать длину видео в кадрах */
    void videoLen(int);
    /* Передать кадр  */
    void updateFrame(QImage*);
    /* Сообщает об остановки видео,
     * если счетчик кадров равен длине видео */
    void stoped();
private slots:
    void update();
private:
    VideoCapture m_video;
    QTimer m_timer;
    QString *m_path;
    QImage *m_frame = nullptr;
    int m_fps = 0;
    int m_frameCount = 0;
};

#endif // VIDEOLOADER_H
