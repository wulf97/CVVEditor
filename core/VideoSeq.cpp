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
    item->endPos = m_pos + startTime;

    m_pos += startTime;
}

void VideoSeq::clearSeq() {
    qDebug() << "slot: clearSeq" << endl;

//    for (int i = 0; i < m_seq.size(); i++) {
//        delete m_seq[i];
//    }

    m_pos = 0;
    m_time = 0;
    m_iVideo = 0;
}

void VideoSeq::loadSeq() {
    qDebug() << "slot: loadSeq" << endl;
    qDebug() << m_seq.size();

    VideoLoader *vLoader = m_core->getVideoLoader();

    m_iVideo = 0;

    if (!m_seq.isEmpty()) {
        emit uploadVideo(m_seq[m_iVideo]->path, false);
        emit setStartTime(m_seq[m_iVideo]->startTime);
        emit setEndTime(m_seq[m_iVideo]->endTime);

        m_iVideo++;
    }

    /* */
    disconnect(m_core, SIGNAL(uploadVideo(QString*, bool)), vLoader, SLOT(uploadVideo(QString*, bool)));
    disconnect(m_core, SIGNAL(unloadVideo()), vLoader, SLOT(unloadVideo()));
    disconnect(m_core, SIGNAL(stopVideo()), vLoader, SLOT(stopVideo()));
    disconnect(m_core, SIGNAL(setTime(int)), vLoader, SLOT(setTime(int)));
    disconnect(m_core, SIGNAL(setStartTime(int)), vLoader, SLOT(setStartTime(int)));
    disconnect(m_core, SIGNAL(setEndTime(int)), vLoader, SLOT(setEndTime(int)));

    connect(m_core, SIGNAL(uploadVideo(QString*, bool)), this, SLOT(seqUploadVideo(QString*, bool)));
    connect(m_core, SIGNAL(setTime(int)), this, SLOT(seqSetTime(int)));

    connect(this, SIGNAL(uploadVideo(QString*, bool)), vLoader, SLOT(uploadVideo(QString*, bool)));
    connect(this, SIGNAL(playVideo()), vLoader, SLOT(playVideo()));
    connect(this, SIGNAL(setTime(int)), vLoader, SLOT(setTime(int)));
    connect(this, SIGNAL(setStartTime(int)), vLoader, SLOT(setStartTime(int)));
    connect(this, SIGNAL(setEndTime(int)), vLoader, SLOT(setEndTime(int)));

    /* */
    connect(vLoader, SIGNAL(ended()), this, SLOT(nextVideo()));
}

void VideoSeq::unloadSeq() {
    qDebug() << "slot: unloadSeq()" << endl;

    VideoLoader *vLoader = m_core->getVideoLoader();
    /* */
    connect(m_core, SIGNAL(uploadVideo(QString*, bool)), vLoader, SLOT(uploadVideo(QString*, bool)));
    connect(m_core, SIGNAL(unloadVideo()), vLoader, SLOT(unloadVideo()));
    connect(m_core, SIGNAL(stopVideo()), vLoader, SLOT(stopVideo()));
    connect(m_core, SIGNAL(setTime(int)), vLoader, SLOT(setTime(int)));
    connect(m_core, SIGNAL(setStartTime(int)), vLoader, SLOT(setStartTime(int)));
    connect(m_core, SIGNAL(setEndTime(int)), vLoader, SLOT(setEndTime(int)));

    disconnect(m_core, SIGNAL(uploadVideo(QString*, bool)), this, SLOT(seqUploadVideo(QString*, bool)));
    disconnect(m_core, SIGNAL(setTime(int)), this, SLOT(seqSetTime(int)));

    disconnect(this, SIGNAL(uploadVideo(QString*, bool)), vLoader, SLOT(uploadVideo(QString*, bool)));
    disconnect(this, SIGNAL(setTime(int)), vLoader, SLOT(setTime(int)));
    disconnect(this, SIGNAL(setStartTime(int)), vLoader, SLOT(setStartTime(int)));
    disconnect(this, SIGNAL(setEndTime(int)), vLoader, SLOT(setEndTime(int)));
}

/************************/
void VideoSeq::seqUploadVideo(QString*, bool) {
    qDebug() << "slot: seqUploadVideo(QString*, bool)" << endl;
}

void VideoSeq::seqSetTime(int) {
    qDebug() << "slot: seqSetTime(int)" << endl;
}

void VideoSeq::nextVideo() {
    qDebug() << "slot: nextVideo()" << endl;
    qDebug() << m_iVideo;

    VideoLoader *vLoader = m_core->getVideoLoader();

    if (m_iVideo < m_seq.size()) {
        qDebug() << m_iVideo;
        emit uploadVideo(m_seq[m_iVideo]->path, false);
        emit setStartTime(m_seq[m_iVideo]->startTime);
        emit setEndTime(m_seq[m_iVideo]->endTime);

        emit playVideo();

        m_iVideo++;
    } else {
        disconnect(vLoader, SIGNAL(ended()), this, SLOT(nextVideo()));
    }
}
