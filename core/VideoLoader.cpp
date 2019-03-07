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
    m_mStartTime = 0;
    m_isOpened = false;

    m_video.open(m_path->toStdString());

    if (m_video.isOpened()) {
        m_isOpened = true;
        m_fps = m_video.get(CAP_PROP_FPS);

        m_video.set(CAP_PROP_POS_AVI_RATIO, 1);
        m_mEndTime = m_video.get(CAP_PROP_POS_MSEC);
        m_video.set(CAP_PROP_POS_MSEC, m_mStartTime);

        if (fl) {
            emit videoLen(m_mEndTime);
        }

        update();
        m_video.release();
        /* Сообщаем о том, что видео было загружено */
        emit uploaded();
    } else {
        qDebug() << "Video can not be load" << endl;
        m_isOpened = false;
        emit error(0);
    }
}

/* Выгрузка видео */
void VideoLoader::unloadVideo() {
    qDebug() << "slot: unloadVideo()" << endl;

    m_isOpened = false;

    m_timer.stop();
    m_video.release();
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
        emit updateTime(0);

        m_mTime = m_mStartTime;
        m_video.set(CAP_PROP_POS_MSEC, m_mStartTime);
        update();

        m_timer.stop();
        m_video.release();
    }
}

/* Приостанавливает отправку кадров */
void VideoLoader::pauseVideo() {
    qDebug() << "slot: pauseVideo()" << endl;

    if (m_isOpened) {
        m_timer.stop();
        if (m_video.isOpened()) {
            m_video.release();
        }
    }
}

/* Установить текущее время */
void VideoLoader::setTime(int time) {
    qDebug() << "slot: setTime(int)" << endl;

    if (m_isOpened) {
//        if (!m_video.isOpened()) {
//            m_video.open(m_path->toStdString());
//        }

        if (m_video.isOpened()) {
            m_mTime = time + m_mStartTime;
            m_video.set(CAP_PROP_POS_MSEC, m_mTime);

//            update();
//            m_video.release();

//            emit pauseVideo();
        }
    }
}

/* Установить начальное время в мсек */
void VideoLoader::setStartTime(int time) {
    qDebug() << "slot: setStartTime(int)" << endl;

    if (m_isOpened) {
        m_mStartTime = time;
        m_video.open(m_path->toStdString());
        if (m_video.isOpened()) {
            m_video.set(CAP_PROP_POS_MSEC, time);
            update();
            m_video.release();
        }
    }
}

/* Установить конечное время в мсек */
void VideoLoader::setEndTime(int time) {
    qDebug() << "slot: setEndTime(int)" << endl;

    if (m_isOpened) {
        m_mEndTime = time;
    }
}

/*************************************/
void VideoLoader::update() {
    Mat frame;

    if (m_video.isOpened()) {
        if (m_mTime < m_mEndTime) {
            m_video >> frame;
            if (!frame.empty()) {
                cvtColor(frame, frame, CV_BGR2RGB);
                m_frame = new QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
                m_mTime = m_video.get(CAP_PROP_POS_MSEC);
                emit updateFrame(m_frame);
                emit updateTime(m_mTime - m_mStartTime);
                delete m_frame;
            }
        } else {
            emit stoped();
            emit ended();
        }
    } else {
        emit updateTime(0);
        emit stoped();
        m_timer.stop();
    }
}
