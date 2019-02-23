#include <QDebug>
#include <QImage>

#include "VideoLoader.h"

VideoLoader::VideoLoader(QObject *parent) : QObject(parent) {

}

void VideoLoader::testSignals() {
    qDebug() << "Response on VideoLoader signals:" << endl;
    qDebug() << "***" << endl;

    emit videoLen(100);
    emit updateFrame(new QImage());
    emit stoped();

    qDebug() << "***" << endl;
}

/******** Описание слотов ********/
/* Загрузка видео */
void VideoLoader::uploadVideo(QString*) {
    qDebug() << "slot: uploadVideo(QString*)" << endl;
}

/* Начинает отправку кадров */
void VideoLoader::playVideo() {
    qDebug() << "slot: playVideo()" << endl;
}

/* Останавливает отправку кадров и сбрасывет счетчик кадров */
void VideoLoader::stopVideo() {
    qDebug() << "slot: stopVideo()" << endl;
}

/* Приостанавливает отправку кадров */
void VideoLoader::pauseVideo() {
    qDebug() << "slot: pauseVideo()" << endl;
}
