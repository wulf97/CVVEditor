#include <QDebug>

#include "VideoSeq.h"
#include "VideoLoader.h"
#include "Core.h"

VideoSeq::VideoSeq(QObject *parent) : QObject(parent) {
    m_core = dynamic_cast<Core*>(parent);
}

void VideoSeq::addToSeq(QString path, int startTime, int endTime) {
    qDebug() << "slot: addToSeq" << endl;

    VideoSeqItem *item = new VideoSeqItem(this);

    m_seq.push_back(item);

    item->path = new QString(path);
    item->startTime = startTime;
    item->endTime = endTime;
    item->startPos = m_pos;
    item->endPos = m_pos + (endTime - startTime);

    m_pos = item->endPos;
}

void VideoSeq::clearSeq() {
    qDebug() << "slot: clearSeq" << endl;

    for (int i = 0; i < m_seq.size(); i++) {
        delete m_seq[i];
    }

    m_seq.clear();

    m_pos = 0;
    m_time = 0;
    m_iVideo = 0;
}

void VideoSeq::loadSeq() {
    qDebug() << "slot: loadSeq" << endl;
    qDebug() << m_seq.size();

    VideoLoader *vLoader = m_core->getVideoLoader();

    m_iVideo = 0;
    m_pos = 0;

    /* */
    disconnect(m_core, SIGNAL(uploadVideo(QString*, bool)), vLoader, SLOT(uploadVideo(QString*, bool)));
    disconnect(m_core, SIGNAL(unloadVideo()), vLoader, SLOT(unloadVideo()));
    disconnect(m_core, SIGNAL(playVideo()), vLoader, SLOT(playVideo()));
    disconnect(m_core, SIGNAL(stopVideo()), vLoader, SLOT(stopVideo()));
    disconnect(m_core, SIGNAL(pauseVideo()), vLoader, SLOT(pauseVideo()));
    disconnect(m_core, SIGNAL(setTime(int)), vLoader, SLOT(setTime(int)));
    disconnect(m_core, SIGNAL(setStartTime(int)), vLoader, SLOT(setStartTime(int)));
    disconnect(m_core, SIGNAL(setEndTime(int)), vLoader, SLOT(setEndTime(int)));

    connect(m_core, SIGNAL(uploadVideo(QString*, bool)), this, SLOT(seqUploadVideo(QString*, bool)));
    connect(m_core, SIGNAL(unloadVideo()), this, SLOT(seqUnloadVideo()));
    connect(m_core, SIGNAL(playVideo()), this, SLOT(seqPlayVideo()));
    connect(m_core, SIGNAL(stopVideo()), this, SLOT(seqStopVideo()));
    connect(m_core, SIGNAL(pauseVideo()), this, SLOT(seqPauseVideo()));
    connect(m_core, SIGNAL(setTime(int)), this, SLOT(seqSetTime(int)));

    connect(this, SIGNAL(uploadVideo(QString*, bool)), vLoader, SLOT(uploadVideo(QString*, bool)));
    connect(this, SIGNAL(unloadVideo()), vLoader, SLOT(unloadVideo()));
    connect(this, SIGNAL(playVideo()), vLoader, SLOT(playVideo()));
    connect(this, SIGNAL(stopVideo()), vLoader, SLOT(stopVideo()));
    connect(this, SIGNAL(pauseVideo()), vLoader, SLOT(pauseVideo()));
    connect(this, SIGNAL(setTime(int)), vLoader, SLOT(setTime(int)));
    connect(this, SIGNAL(setStartTime(int)), vLoader, SLOT(setStartTime(int)));
    connect(this, SIGNAL(setEndTime(int)), vLoader, SLOT(setEndTime(int)));

    /* */
    connect(vLoader, SIGNAL(ended()), this, SLOT(nextVideo()));
    connect(vLoader, SIGNAL(uploaded()), this, SLOT(uploaded()));

    /***********/
    disconnect(vLoader, SIGNAL(updateTime(int)), m_core, SIGNAL(updateTime(int)));

    connect(vLoader, SIGNAL(updateTime(int)), this, SLOT(seqUpdateTime(int)));
    connect(this, SIGNAL(updateTime(int)), m_core, SIGNAL(updateTime(int)));

    /******************/
    nextVideo();
}

void VideoSeq::unloadSeq() {
    qDebug() << "slot: unloadSeq()" << endl;

    VideoLoader *vLoader = m_core->getVideoLoader();
    /* */
    connect(m_core, SIGNAL(uploadVideo(QString*, bool)), vLoader, SLOT(uploadVideo(QString*, bool)));
    connect(m_core, SIGNAL(unloadVideo()), vLoader, SLOT(unloadVideo()));
    connect(m_core, SIGNAL(playVideo()), vLoader, SLOT(playVideo()));
    connect(m_core, SIGNAL(stopVideo()), vLoader, SLOT(stopVideo()));
    connect(m_core, SIGNAL(pauseVideo()), vLoader, SLOT(pauseVideo()));
    connect(m_core, SIGNAL(setTime(int)), vLoader, SLOT(setTime(int)));
    connect(m_core, SIGNAL(setStartTime(int)), vLoader, SLOT(setStartTime(int)));
    connect(m_core, SIGNAL(setEndTime(int)), vLoader, SLOT(setEndTime(int)));

    disconnect(m_core, SIGNAL(uploadVideo(QString*, bool)), this, SLOT(seqUploadVideo(QString*, bool)));
    disconnect(m_core, SIGNAL(unloadVideo()), this, SLOT(seqUnloadVideo()));
    disconnect(m_core, SIGNAL(playVideo()), this, SLOT(seqPlayVideo()));
    disconnect(m_core, SIGNAL(stopVideo()), this, SLOT(seqStopVideo()));
    disconnect(m_core, SIGNAL(pauseVideo()), this, SLOT(seqPauseVideo()));
    disconnect(m_core, SIGNAL(setTime(int)), this, SLOT(seqSetTime(int)));

    disconnect(this, SIGNAL(uploadVideo(QString*, bool)), vLoader, SLOT(uploadVideo(QString*, bool)));
    disconnect(this, SIGNAL(unloadVideo()), vLoader, SLOT(unloadVideo()));
    disconnect(this, SIGNAL(playVideo()), vLoader, SLOT(playVideo()));
    disconnect(this, SIGNAL(stopVideo()), vLoader, SLOT(stopVideo()));
    disconnect(this, SIGNAL(pauseVideo()), vLoader, SLOT(pauseVideo()));
    disconnect(this, SIGNAL(setTime(int)), vLoader, SLOT(setTime(int)));
    disconnect(this, SIGNAL(setStartTime(int)), vLoader, SLOT(setStartTime(int)));
    disconnect(this, SIGNAL(setEndTime(int)), vLoader, SLOT(setEndTime(int)));

    /* */
    disconnect(vLoader, SIGNAL(ended()), this, SLOT(nextVideo()));
    disconnect(vLoader, SIGNAL(uploaded()), this, SLOT(uploaded()));

    /***********/
    connect(vLoader, SIGNAL(updateTime(int)), m_core, SIGNAL(updateTime(int)));

    disconnect(vLoader, SIGNAL(updateTime(int)), this, SLOT(seqUpdateTime(int)));
    disconnect(this, SIGNAL(updateTime(int)), m_core, SIGNAL(updateTime(int)));

    /******************/
}

/************************/
void VideoSeq::seqUploadVideo(QString*, bool) {
    qDebug() << "slot: seqUploadVideo(QString*, bool)" << endl;
}

void VideoSeq::seqUnloadVideo() {
    qDebug() << "slot: seqUnloadVideo()" << endl;
}

void VideoSeq::seqPlayVideo() {
    qDebug() << "slot: seqPlayVideo()" << endl;

    emit playVideo();
}

void VideoSeq::seqStopVideo() {
    qDebug() << "slot: seqStopVideo()" << endl;

    if (!m_seq.isEmpty()) {
        m_iVideo = 0;

        nextVideo();
        emit stopVideo();
        emit updateTime(0);
        emit stopVideo();
    }
}

void VideoSeq::seqPauseVideo() {
    qDebug() << "slot: seqPauseVideo()" << endl;

    emit pauseVideo();
}

void VideoSeq::seqSetTime(int) {
    qDebug() << "slot: seqSetTime(int)" << endl;
}

void VideoSeq::seqUpdateTime(int time) {
    qDebug() << "slot: seqUpdateTime(int)" << endl;

    emit updateTime(m_pos + time);
    qDebug() << m_pos;
}


void VideoSeq::nextVideo() {
    qDebug() << "slot: nextVideo()" << endl;

    VideoLoader *vLoader = m_core->getVideoLoader();

    if (m_iVideo < m_seq.size()) {
        qDebug() << "i: " << m_iVideo << " " << *(m_seq[m_iVideo]->path);
        emit uploadVideo(m_seq[m_iVideo]->path, false);
    } else {
        disconnect(vLoader, SIGNAL(ended()), this, SLOT(nextVideo()));
        disconnect(vLoader, SIGNAL(uploaded()), this, SLOT(uploaded()));
    }
}

void VideoSeq::uploaded() {
    qDebug() << "slot: uploaded()" << endl;

    VideoLoader *vLoader = m_core->getVideoLoader();

    emit setStartTime(m_seq[m_iVideo]->startTime);
    emit setEndTime(m_seq[m_iVideo]->endTime);
    emit setTime(0);
    emit playVideo();

    m_pos = m_seq[m_iVideo]->startPos;

    m_iVideo++;
}
