#ifndef VIDEOLOADER_H
#define VIDEOLOADER_H

#include <QObject>

class VideoLoader : public QObject {
    Q_OBJECT
public:
    VideoLoader(QObject *parent = nullptr);

    void testSignals();
public slots:
    /* Загрузка видео */
    void uploadVideo(QString*);
    /* Начинает отправку кадров */
    void playVideo();
    /* Останавливает отправку кадров и сбрасывет счетчик кадров */
    void stopVideo();
    /* Приостанавливает отправку кадров */
    void pauseVideo();
signals:
    /* Передает длину видео в кадрах */
    void videoLen(int);
    /* Передает кадр  */
    void updateFrame(QImage*);
    /* Сообщает об остановки видео,
     * если счетчик кадров равен длине видео */
    void stoped();
};

#endif // VIDEOLOADER_H
