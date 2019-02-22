#include <QDebug>

#include "VideoLoader.h"

VideoLoader::VideoLoader(QObject *parent) : QObject(parent) {

}

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
