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
    void uploadVideo(QString*, bool);
    /* Выгрузка видео */
    void unloadVideo();
    void writeVideo(VideoWriter*);
    /* Начать отправку кадров */
    void playVideo();
    /* Останавливить отправку кадров и сбрасить счетчик кадров */
    void stopVideo();
    /* Приостанавить отправку кадров */
    void pauseVideo();
    /* Установить текущее время */
    void setTime(int);
    /* Установить начальное время в мсек */
    void setStartTime(int);
    /* Установить конечный время в мсек */
    void setEndTime(int);
signals:
    /* Метод для отлавливания ошибок */
    void error(int);

    /* Передать длину видео в мсек */
    void videoLen(int);
    /* */
    void uploaded();
    /* Передать кадр  */
    void updateFrame(QImage*);
    /* Сообщает об остановки видео,
     * если счетчик кадров равен длине видео */
    void stoped();
    /* Передает текущее время в мсек */
    void updateTime(int);
    /* */
    void ended();
private slots:
    void update();
    void updateWritedFrame();
private:
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
