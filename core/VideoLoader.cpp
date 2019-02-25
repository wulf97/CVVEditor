#include <QDebug>
#include <QImage>

#include "VideoLoader.h"


VideoLoader::VideoLoader(QObject *parent) : QObject(parent) {
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
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
void VideoLoader::uploadVideo(QString *path, bool fl) {
    qDebug() << "slot: uploadVideo(QString*)" << endl;

    m_path = new QString(*path);
    m_mTime = 0;
    m_video.open(m_path->toStdString());

    if (m_video.isOpened()) {
        m_isOpened = true;
        m_fps = m_video.get(CAP_PROP_FPS);

        if (fl) {
            emit videoLen(m_video.get(CAP_PROP_FRAME_COUNT)/m_fps*1000);
        }

        update();
        m_video.release();
    } else {
        qDebug() << "Video can not be load" << endl;
        m_isOpened = false;
        emit error(0);
    }
}

/* Начинает отправку кадров */
void VideoLoader::playVideo() {
    qDebug() << "slot: playVideo()" << endl;

    if (m_isOpened) {
        m_video.open(m_path->toStdString());

        if (m_video.isOpened()) {
            m_video.set(CAP_PROP_POS_MSEC, m_mTime);
            m_timer.start(1000/m_fps);
        }
    }
}

/* Останавливает отправку кадров и сбрасывет счетчик кадров */
void VideoLoader::stopVideo() {
    qDebug() << "slot: stopVideo()" << endl;

    if (m_isOpened) {
        emit stoped();

        m_mTime = 1000/m_fps;
        m_video.set(CAP_PROP_POS_MSEC, m_mTime);
        update();

        m_timer.stop();
        m_video.release();
    }
}

/* Приостанавливает отправку кадров */
void VideoLoader::pauseVideo() {
    qDebug() << "slot: pauseVideo()" << endl;

    if (m_isOpened) {
        m_mTime = m_video.get(CAP_PROP_POS_MSEC);
        m_timer.stop();
        m_video.release();
    }
}

/*************************************/
void VideoLoader::update() {
    Mat frame;

    if (m_video.isOpened()) {
        m_video >> frame;
        if (!frame.empty()) {
            cvtColor(frame, frame, CV_BGR2RGB);
            m_frame = new QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
            emit updateFrame(m_frame);
        }
    } else {
        emit stoped();
        m_timer.stop();
    }
}
