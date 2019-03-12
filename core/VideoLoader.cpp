#include <QDebug>
#include <QImage>

#include "VideoLoader.h"


VideoLoader::VideoLoader(QObject *parent) : QObject(parent) {
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    connect(&m_timer2, SIGNAL(timeout()), this, SLOT(updateWritedFrame()));
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

void VideoLoader::writeVideo(VideoWriter *out) {
    qDebug() << "slot: writeVideo()" << endl;
    if (m_isOpened) {
        m_outVideo = out;
        m_time = m_startTime;
        m_video.open(m_path->toStdString());

        if (m_video.isOpened()) {
            m_video.set(CAP_PROP_POS_MSEC, m_startTime);
            m_timer2.start();
        }
    }
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

/* Останавливает отправку кадров и сбрасывет счетчик кадров */
void VideoLoader::stopVideo() {
    qDebug() << "slot: stopVideo()" << endl;

    if (m_isOpened) {
        if (m_endTime - m_startTime != 0) {
            m_time = m_startTime;
            m_video.set(CAP_PROP_POS_MSEC, m_startTime);
            update();
        }

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
            update();
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
void VideoLoader::update() {
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
            emit stoped();
            emit ended();
        }
    } else {
        emit updateTime(0);
        emit stoped();
        m_timer.stop();
    }
}

void VideoLoader::updateWritedFrame() {
   // qDebug() << "slot: updateWritedFrame()" << endl;

    Mat frame;

    if (m_video.isOpened()) {
        if (m_time < m_endTime) {
            m_video >> frame;
            if (!frame.empty()) {
                resize(frame, frame, Size(500, 400));
                m_outVideo->write(frame);
                m_time = m_video.get(CAP_PROP_POS_MSEC);
                update();
            }
        } else {
//            m_isOpened = false;
            m_timer2.stop();
            emit ended();
        }
    } else {
        m_timer2.stop();
    }
}
