#include <QDebug>

#include "VideoSeq.h"
#include "Core.h"

using namespace cv;

VideoSeq::VideoSeq(QObject *parent) : QObject(parent) {
    m_parent = dynamic_cast<Core*>(parent);
    m_vLoader = m_parent->getVideoLoader();

    connect(m_parent, SIGNAL(clearSeq()), this, SLOT(clearSeq()));
    connect(m_parent, SIGNAL(addToSeq(QString,int,int)), this, SLOT(addToSeq(QString,int,int)));
    connect(m_parent, SIGNAL(loadSeq()), this, SLOT(loadSeq()));
    connect(m_parent, SIGNAL(unloadSeq()), this, SLOT(unloadSeq()));
    connect(m_parent, SIGNAL(saveSeq(QString)), this, SLOT(saveSeq(QString)));

    connect(&m_displayTimer, SIGNAL(timeout()), this, SLOT(updateDisplayedFrame()));
    connect(&m_saveTimer, SIGNAL(timeout()), this, SLOT(updateWritedFrame()));
}

void VideoSeq::setConnection() {
    /* Подключение к ядру */
    /* Сигналы идущие к VideoSeq */
    connect(m_parent, SIGNAL(playVideo()), this, SLOT(seqPlayVideo()));
    connect(m_parent, SIGNAL(pauseVideo()), this, SLOT(seqPauseVideo()));
    connect(m_parent, SIGNAL(stopVideo()), this, SLOT(seqStopVideo()));
    connect(m_parent, SIGNAL(setTime(int)), this, SLOT(seqSetTime(int)));

    /* Сигналы идущие от VideoSeq */
    connect(this, SIGNAL(updateFrame(QImage*)), m_parent, SIGNAL(updateFrame(QImage*)));
    connect(this, SIGNAL(updateTime(int)), m_parent, SIGNAL(updateTime(int)));
    connect(this, SIGNAL(isUploaded()), m_parent, SIGNAL(isUploaded()));
    connect(this, SIGNAL(isPlayed()), m_parent, SIGNAL(isPlayed()));
    connect(this, SIGNAL(isPaused()), m_parent, SIGNAL(isPaused()));
    connect(this, SIGNAL(isStoped()), m_parent, SIGNAL(isStoped()));
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

    m_parent->disconnect(m_parent->getVideoLoader());
    m_parent->getVideoLoader()->disconnect();
    setConnection();

    seqUploadVideo(0);
}

void VideoSeq::unloadSeq() {
    m_parent->getVideoLoader()->setConnection();
    m_parent->disconnect(this);
    disconnect();

    connect(m_parent, SIGNAL(clearSeq()), this, SLOT(clearSeq()));
    connect(m_parent, SIGNAL(addToSeq(QString,int,int)), this, SLOT(addToSeq(QString,int,int)));
    connect(m_parent, SIGNAL(loadSeq()), this, SLOT(loadSeq()));
    connect(m_parent, SIGNAL(unloadSeq()), this, SLOT(unloadSeq()));
    connect(m_parent, SIGNAL(saveSeq(QString)), this, SLOT(saveSeq(QString)));
}

void VideoSeq::saveSeq(QString fileName) {
    qDebug() << "slot saveSeq(QString)" << endl;
    m_it = 0;
    m_time = 0;

    m_outVideo.open(fileName.toStdString(), CV_FOURCC('M','J','P','G'), 24, Size(500, 400));
    m_inVideo.open(m_seq[m_it]->path->toStdString());
    m_inVideo.set(CAP_PROP_POS_MSEC, m_seq[m_it]->startTime);

    m_saveTimer.start();

    connect(this, SIGNAL(updateProgress(int)), m_parent, SIGNAL(updateProgress(int)));
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

/***************/
void VideoSeq::updateDisplayedFrame() {
    Mat frame;

    if (m_inVideo.isOpened()) {
        if (m_time < m_seq[m_it]->endPos) {
            m_inVideo >> frame;
            if (!frame.empty()) {
                cvtColor(frame, frame, CV_BGR2RGB);
                m_frame = new QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
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
                disconnect(this, SIGNAL(updateProgress(int)), m_parent, SIGNAL(updateProgress(int)));
            }
        }
    }
}
