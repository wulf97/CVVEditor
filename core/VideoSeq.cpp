#include <QDebug>

#include "VideoSeq.h"
#include "Core.h"
#include "VideoSeqEffects.h"

using namespace cv;

VideoSeq::VideoSeq(QObject *parent) : QObject(parent) {
    m_core = dynamic_cast<Core*>(parent);
    m_state = STATE::IS_STOPED;
    m_it = 0;
    m_fps = 0;
    m_pos = 0;
    m_time = 0;

    connect(m_core, SIGNAL(clearSeq()), this, SLOT(clearSeq()));
    connect(m_core, SIGNAL(addToSeq(QString,int,int)), this, SLOT(addToSeq(QString,int,int)));
    connect(m_core, SIGNAL(loadSeq()), this, SLOT(loadSeq()));
    connect(m_core, SIGNAL(unloadSeq()), this, SLOT(unloadSeq()));
    connect(m_core, SIGNAL(saveSeq(QString)), this, SLOT(saveSeq(QString)));
    connect(m_core, SIGNAL(addEffect(int,int,QString)), this, SLOT(addEffect(int,int,QString)));

    connect(&m_displayTimer, SIGNAL(timeout()), this, SLOT(updateDisplayedFrame()));
    connect(&m_saveTimer, SIGNAL(timeout()), this, SLOT(updateWritedFrame()));
}

Core *VideoSeq::getParent() {
    return m_core;
}

void VideoSeq::setConnection() {
    /* Подключение к ядру */
    /* Сигналы идущие к VideoSeq */
    connect(m_core, SIGNAL(playVideo()), this, SLOT(seqPlayVideo()));
    connect(m_core, SIGNAL(pauseVideo()), this, SLOT(seqPauseVideo()));
    connect(m_core, SIGNAL(stopVideo()), this, SLOT(seqStopVideo()));
    connect(m_core, SIGNAL(setTime(int)), this, SLOT(seqSetTime(int)));

    /* Сигналы идущие от VideoSeq */
    connect(this, SIGNAL(updateFrame(QImage*)), m_core, SIGNAL(updateFrame(QImage*)));
    connect(this, SIGNAL(updateTime(int)), m_core, SIGNAL(updateTime(int)));
    connect(this, SIGNAL(isUploaded()), m_core, SIGNAL(isUploaded()));
    connect(this, SIGNAL(isPlayed()), m_core, SIGNAL(isPlayed()));
    connect(this, SIGNAL(isPaused()), m_core, SIGNAL(isPaused()));
    connect(this, SIGNAL(isStoped()), m_core, SIGNAL(isStoped()));
}

/**/
void VideoSeq::clearSeq() {
    qDebug() << "slot: clearSeq()" << endl;

    m_pos = 0;
    m_time = 0;
    m_it = 0;

    for (int i = 0; i < m_seq.size(); i++) {
        delete m_seq[i];
    }

    m_seq.clear();
    disconnect();
}

void VideoSeq::addToSeq(QString path, int startTime, int endTime) {
    qDebug() << "slot: addToSeq(QString, int, int)" << endl;

    VideoSeqItem *item = new VideoSeqItem(this);

    m_seq.push_back(item);

    item->path = new QString(path);
    item->startTime = startTime;
    item->endTime = endTime;
    item->startPos = m_pos;
    item->endPos = m_pos + (endTime - startTime);

    m_pos = item->endPos;
}

void VideoSeq::loadSeq() {
    qDebug() << "slot: loadSeq()" << endl;

    m_it = 0;
    m_state = STATE::IS_STOPED;

    m_core->disconnect(m_core->getVideoLoader());
    m_core->getVideoLoader()->disconnect();
    setConnection();

    seqUploadVideo(0);
}

void VideoSeq::unloadSeq() {
    m_core->getVideoLoader()->setConnection();
    m_core->disconnect(this);
    disconnect();

    connect(m_core, SIGNAL(clearSeq()), this, SLOT(clearSeq()));
    connect(m_core, SIGNAL(addToSeq(QString,int,int)), this, SLOT(addToSeq(QString,int,int)));
    connect(m_core, SIGNAL(loadSeq()), this, SLOT(loadSeq()));
    connect(m_core, SIGNAL(unloadSeq()), this, SLOT(unloadSeq()));
    connect(m_core, SIGNAL(saveSeq(QString)), this, SLOT(saveSeq(QString)));
}

void VideoSeq::saveSeq(QString fileName) {
    qDebug() << "slot saveSeq(QString)" << endl;
    m_it = 0;
    m_time = 0;

    m_outVideo.open(fileName.toStdString(), CV_FOURCC('M','J','P','G'), 24, Size(500, 400));
    m_inVideo.open(m_seq[m_it]->path->toStdString());
    m_inVideo.set(CAP_PROP_POS_MSEC, m_seq[m_it]->startTime);

    m_saveTimer.start();

    connect(this, SIGNAL(updateProgress(int)), m_core, SIGNAL(updateProgress(int)));
}

/************************/
void VideoSeq::seqUploadVideo(int time) {
    qDebug() << "slot: seqUploadVideo(int)" << endl;
    m_inVideo.open(m_seq[m_it]->path->toStdString());

    if (m_inVideo.isOpened()) {
        m_fps = m_inVideo.get(CAP_PROP_FPS);
        m_time = m_seq[m_it]->startPos + time;

        m_inVideo.release();

        switch (m_state) {
            case STATE::IS_PLAYED:
                seqPlayVideo();
            break;
            case STATE::IS_PAUSED:
                seqPauseVideo();
            break;
            case STATE::IS_STOPED:
                seqStopVideo();
            break;
        }
    }
}

void VideoSeq::seqWriteVideo() {
    qDebug() << "slot: seqWriteVideo()" << endl;
}

void VideoSeq::seqPlayVideo() {
    qDebug() << "slot: seqPlayVideo()" << endl;
    m_state = STATE::IS_PLAYED;

    m_inVideo.open(m_seq[m_it]->path->toStdString());

    if (m_inVideo.isOpened()) {
        m_inVideo.set(CAP_PROP_POS_MSEC, m_seq[m_it]->startTime + m_time - m_seq[m_it]->startPos);
        m_displayTimer.start(1000/m_fps);
    }
}

void VideoSeq::seqPauseVideo() {
    qDebug() << "slot: seqPauseVideo()" << endl;

    m_state = STATE::IS_PAUSED;

    m_displayTimer.stop();
    m_inVideo.release();

    emit isPaused();
}

void VideoSeq::seqStopVideo() {
    qDebug() << "slot: seqStopVideo()" << endl;

    m_state = STATE::IS_STOPED;
    m_time = 0;

    m_displayTimer.stop();
    m_inVideo.release();

    emit updateTime(0);
    emit isStoped();
}

void VideoSeq::seqSetTime(int time) {
    qDebug() << "slot: seqSetTime(int)" << endl;

    if (time < m_seq[m_it]->endPos && time > m_seq[m_it]->startPos) {
        m_time = time;
        m_inVideo.set(CAP_PROP_POS_MSEC, time - m_seq[m_it]->startPos);
        emit updateTime(m_time);
    } else {
        for (int i = 0; i < m_seq.size(); i++) {
            if (time < m_seq[i]->endPos && time > m_seq[i]->startPos) {
                m_it = i;
                seqUploadVideo(time - m_seq[i]->startPos);
                break;
            }
        }
    }
}

void VideoSeq::addEffect(int startTime, int endTime, QString effectName) {
    VideoSeqEffects *effect = new VideoSeqEffects(this);
    effect->setStartTime(startTime);
    effect->setEndTime(endTime);
    effect->addEffect(m_core->getPluginManager()->getByName(effectName));
    m_effects.push_back(effect);
}

/***************/
void VideoSeq::updateDisplayedFrame() {
    Mat frame;

    if (m_inVideo.isOpened()) {
        if (m_time < m_seq[m_it]->endPos) {
            m_inVideo >> frame;
            if (!frame.empty()) {
                /**/
                for (int i = 0; i < m_effects.size(); i++) {
                    if (m_effects[i]->getStartTime() <= m_time &&
                        m_time < m_effects[i]->getEndTime()) {
                        m_effects[i]->handle(frame);
                    }
                }
                /**/
                if (frame.channels() == 3) {
                    cvtColor(frame, frame, CV_BGR2RGB);
                    m_frame = new QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
                } else if (frame.channels() == 1) {
                    m_frame = new QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_Grayscale8);
                }

                m_time = m_seq[m_it]->startPos - m_seq[m_it]->startTime + m_inVideo.get(CAP_PROP_POS_MSEC);

                emit updateFrame(m_frame);
                emit updateTime(m_time);
                delete m_frame;
            }
        } else {
            if (m_it < m_seq.size() - 1) {
                m_it++;
                seqUploadVideo(0);
            } else {
                m_it = 0;
                seqStopVideo();
            }
        }
    }
}

void VideoSeq::updateWritedFrame() {
    Mat frame;

    if (m_inVideo.isOpened()) {
        if (m_time < m_seq[m_it]->endPos) {
            m_inVideo >> frame;
            if (!frame.empty()) {
                m_time = m_seq[m_it]->startPos - m_seq[m_it]->startTime + m_inVideo.get(CAP_PROP_POS_MSEC);
                resize(frame, frame, Size(500, 400));
                m_outVideo.write(frame);
                emit updateProgress((100./m_seq[m_seq.size() - 1]->endPos)*m_time);
            }
        } else {
            if (m_it < m_seq.size() - 1) {
                m_it++;
                m_inVideo.release();
                m_inVideo.open(m_seq[m_it]->path->toStdString());
                m_inVideo.set(CAP_PROP_POS_MSEC, m_seq[m_it]->startTime + m_time - m_seq[m_it]->startPos);
            } else {
                m_it = 0;
                m_saveTimer.stop();
                m_outVideo.release();
                disconnect(this, SIGNAL(updateProgress(int)), m_core, SIGNAL(updateProgress(int)));
            }
        }
    }
}
