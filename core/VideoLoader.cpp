#include <QDebug>
#include <QImage>

#include "VideoLoader.h"
#include "Core.h"

VideoLoader::VideoLoader(QObject *parent) : QObject(parent) {
    m_parent = dynamic_cast<Core*>(parent);

    setConnection();
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(updateDisplayedFrame()));
}

void VideoLoader::setConnection() {
    /* Подключение к ядру */
    /* Сигналы идущие к VideoLoader */
    connect(m_parent, SIGNAL(uploadVideo(QString*, bool)), this, SLOT(uploadVideo(QString*, bool)));
    connect(m_parent, SIGNAL(unloadVideo()), this, SLOT(unloadVideo()));
    connect(m_parent, SIGNAL(playVideo()), this, SLOT(playVideo()));
    connect(m_parent, SIGNAL(pauseVideo()), this, SLOT(pauseVideo()));
    connect(m_parent, SIGNAL(stopVideo()), this, SLOT(stopVideo()));
    connect(m_parent, SIGNAL(setTime(int)), this, SLOT(setTime(int)));
    connect(m_parent, SIGNAL(setStartTime(int)), this, SLOT(setStartTime(int)));
    connect(m_parent, SIGNAL(setEndTime(int)), this, SLOT(setEndTime(int)));

    /* Сигналы идущие от VideoLoader */
    connect(this, SIGNAL(videoLen(int)), m_parent, SIGNAL(videoLen(int)));
    connect(this, SIGNAL(updateFrame(QImage*)), m_parent, SIGNAL(updateFrame(QImage*)));
    connect(this, SIGNAL(isStoped()), m_parent, SIGNAL(isStoped()));
    connect(this, SIGNAL(updateTime(int)), m_parent, SIGNAL(updateTime(int)));
}

/******** Описание слотов ********/
/* Загрузка видео */
void VideoLoader::uploadVideo(QString *path, bool fl) {
    qDebug() << "slot: uploadVideo(QString*)" << endl;

    m_path = new QString(*path);
    m_time = 0;
    m_startTime = 0;
    m_isOpened = false;

    m_video.open(m_path->toStdString());

    if (m_video.isOpened()) {
        m_isOpened = true;
        m_fps = m_video.get(CAP_PROP_FPS);

        m_video.set(CAP_PROP_POS_AVI_RATIO, 1);
        m_endTime = m_video.get(CAP_PROP_POS_MSEC);
        m_video.set(CAP_PROP_POS_MSEC, m_startTime);

        if (fl) {
            emit videoLen(m_endTime);
        }

        updateDisplayedFrame();
        m_video.release();
    } else {
        qDebug() << "Video can not be load" << endl;
        m_isOpened = false;
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
            m_video.set(CAP_PROP_POS_MSEC, m_time);
            m_timer.start(1000/m_fps);
        }
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

/* Останавливает отправку кадров и сбрасывет счетчик кадров */
void VideoLoader::stopVideo() {
    qDebug() << "slot: stopVideo()" << endl;

    if (m_isOpened) {
        if (m_endTime - m_startTime != 0) {
            m_time = m_startTime;
            m_video.set(CAP_PROP_POS_MSEC, m_startTime);
            updateDisplayedFrame();
        }

        m_timer.stop();
        m_video.release();
    }
}

/* Установить текущее время */
void VideoLoader::setTime(int time) {
    qDebug() << "slot: setTime(int)" << endl;

    if (m_isOpened) {
        m_time = time + m_startTime;

        if (m_video.isOpened()) {
            m_video.set(CAP_PROP_POS_MSEC, m_time);
        }
    }
}

/* Установить начальное время в мсек */
void VideoLoader::setStartTime(int time) {
    qDebug() << "slot: setStartTime(int)" << endl;

    if (m_isOpened) {
        m_startTime = time;
        m_video.open(m_path->toStdString());
        if (m_video.isOpened()) {
            m_video.set(CAP_PROP_POS_MSEC, time);
            updateDisplayedFrame();
            m_video.release();
        }
    }
}

/* Установить конечное время в мсек */
void VideoLoader::setEndTime(int time) {
    qDebug() << "slot: setEndTime(int)" << endl;

    if (m_isOpened) {
        m_endTime = time;
    }
}

/*************************************/
void VideoLoader::updateDisplayedFrame() {
    Mat frame;

    if (m_video.isOpened()) {
        if (m_time < m_endTime) {
            m_video >> frame;
            if (!frame.empty()) {
                cvtColor(frame, frame, CV_BGR2RGB);
                m_frame = new QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
                m_time = m_video.get(CAP_PROP_POS_MSEC);
                emit updateFrame(m_frame);
                emit updateTime(m_time - m_startTime);
                delete m_frame;
            }
        } else {
            stopVideo();
            emit isStoped();
        }
    } else {
        emit updateTime(0);
        emit isStoped();
        m_timer.stop();
    }
}
