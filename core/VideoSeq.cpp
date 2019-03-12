#include <QDebug>

#include "VideoSeq.h"
#include "VideoLoader.h"
#include "Core.h"

using namespace cv;

VideoSeq::VideoSeq(QObject *parent) : QObject(parent) {
    m_parent = dynamic_cast<Core*>(parent);
    m_vLoader = m_parent->getVideoLoader();
    m_outVideo = new VideoWriter();

    connect(this, SIGNAL(writeVideo(VideoWriter*)), m_parent->getVideoLoader(), SLOT(writeVideo(VideoWriter*)));
}


void VideoSeq::setConnect() {

}

void VideoSeq::setDisconnect() {

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

void VideoSeq::clearSeq() {
    qDebug() << "slot: clearSeq()" << endl;

    for (int i = 0; i < m_seq.size(); i++) {
        delete m_seq[i];
    }

    m_seq.clear();

    m_pos = 0;
    m_time = 0;
    m_iVideo = 0;
}

void VideoSeq::loadSeq() {
    qDebug() << "slot: loadSeq()" << endl;

    m_iVideo = 0;
    m_pos = 0;

    /* */
    disconnect(m_parent, SIGNAL(uploadVideo(QString*, bool)), m_vLoader, SLOT(uploadVideo(QString*, bool)));
    disconnect(m_parent, SIGNAL(unloadVideo()), m_vLoader, SLOT(unloadVideo()));
    disconnect(m_parent, SIGNAL(playVideo()), m_vLoader, SLOT(playVideo()));
    disconnect(m_parent, SIGNAL(stopVideo()), m_vLoader, SLOT(stopVideo()));
    disconnect(m_parent, SIGNAL(pauseVideo()), m_vLoader, SLOT(pauseVideo()));
    disconnect(m_parent, SIGNAL(setTime(int)), m_vLoader, SLOT(setTime(int)));
    disconnect(m_parent, SIGNAL(setStartTime(int)), m_vLoader, SLOT(setStartTime(int)));
    disconnect(m_parent, SIGNAL(setEndTime(int)), m_vLoader, SLOT(setEndTime(int)));

    connect(m_parent, SIGNAL(uploadVideo(QString*, bool)), this, SLOT(seqUploadVideo(QString*, bool)));
    connect(m_parent, SIGNAL(unloadVideo()), this, SLOT(seqUnloadVideo()));
    connect(m_parent, SIGNAL(playVideo()), this, SLOT(seqPlayVideo()));
    connect(m_parent, SIGNAL(stopVideo()), this, SLOT(seqStopVideo()));
    connect(m_parent, SIGNAL(pauseVideo()), this, SLOT(seqPauseVideo()));
    connect(m_parent, SIGNAL(setTime(int)), this, SLOT(seqSetTime(int)));

    connect(this, SIGNAL(uploadVideo(QString*, bool)), m_vLoader, SLOT(uploadVideo(QString*, bool)));
    connect(this, SIGNAL(unloadVideo()), m_vLoader, SLOT(unloadVideo()));
    connect(this, SIGNAL(playVideo()), m_vLoader, SLOT(playVideo()));
    connect(this, SIGNAL(stopVideo()), m_vLoader, SLOT(stopVideo()));
    connect(this, SIGNAL(pauseVideo()), m_vLoader, SLOT(pauseVideo()));
    connect(this, SIGNAL(setTime(int)), m_vLoader, SLOT(setTime(int)));
    connect(this, SIGNAL(setStartTime(int)), m_vLoader, SLOT(setStartTime(int)));
    connect(this, SIGNAL(setEndTime(int)), m_vLoader, SLOT(setEndTime(int)));

    /* */
    connect(m_vLoader, SIGNAL(ended()), this, SLOT(nextVideoDisplay()));
    connect(m_vLoader, SIGNAL(uploaded()), this, SLOT(uploaded()));

    /***********/
    disconnect(m_vLoader, SIGNAL(updateTime(int)), m_parent, SIGNAL(updateTime(int)));
    disconnect(m_vLoader, SIGNAL(stoped()), m_parent, SIGNAL(stoped()));

    connect(m_vLoader, SIGNAL(updateTime(int)), this, SLOT(seqUpdateTime(int)));
    connect(this, SIGNAL(updateTime(int)), m_parent, SIGNAL(updateTime(int)));
    connect(this, SIGNAL(stoped()), m_parent, SIGNAL(stoped()));

    /******************/
    nextVideoDisplay();
}

void VideoSeq::unloadSeq() {
    qDebug() << "slot: unloadSeq()" << endl;

    /* */
    connect(m_parent, SIGNAL(uploadVideo(QString*, bool)), m_vLoader, SLOT(uploadVideo(QString*, bool)));
    connect(m_parent, SIGNAL(unloadVideo()), m_vLoader, SLOT(unloadVideo()));
    connect(m_parent, SIGNAL(playVideo()), m_vLoader, SLOT(playVideo()));
    connect(m_parent, SIGNAL(stopVideo()), m_vLoader, SLOT(stopVideo()));
    connect(m_parent, SIGNAL(pauseVideo()), m_vLoader, SLOT(pauseVideo()));
    connect(m_parent, SIGNAL(setTime(int)), m_vLoader, SLOT(setTime(int)));
    connect(m_parent, SIGNAL(setStartTime(int)), m_vLoader, SLOT(setStartTime(int)));
    connect(m_parent, SIGNAL(setEndTime(int)), m_vLoader, SLOT(setEndTime(int)));

    disconnect(m_parent, SIGNAL(uploadVideo(QString*, bool)), this, SLOT(seqUploadVideo(QString*, bool)));
    disconnect(m_parent, SIGNAL(unloadVideo()), this, SLOT(seqUnloadVideo()));
    disconnect(m_parent, SIGNAL(playVideo()), this, SLOT(seqPlayVideo()));
    disconnect(m_parent, SIGNAL(stopVideo()), this, SLOT(seqStopVideo()));
    disconnect(m_parent, SIGNAL(pauseVideo()), this, SLOT(seqPauseVideo()));
    disconnect(m_parent, SIGNAL(setTime(int)), this, SLOT(seqSetTime(int)));

    disconnect(this, SIGNAL(uploadVideo(QString*, bool)), m_vLoader, SLOT(uploadVideo(QString*, bool)));
    disconnect(this, SIGNAL(unloadVideo()), m_vLoader, SLOT(unloadVideo()));
    disconnect(this, SIGNAL(playVideo()), m_vLoader, SLOT(playVideo()));
    disconnect(this, SIGNAL(stopVideo()), m_vLoader, SLOT(stopVideo()));
    disconnect(this, SIGNAL(pauseVideo()), m_vLoader, SLOT(pauseVideo()));
    disconnect(this, SIGNAL(setTime(int)), m_vLoader, SLOT(setTime(int)));
    disconnect(this, SIGNAL(setStartTime(int)), m_vLoader, SLOT(setStartTime(int)));
    disconnect(this, SIGNAL(setEndTime(int)), m_vLoader, SLOT(setEndTime(int)));

    /* */
    disconnect(m_vLoader, SIGNAL(ended()), this, SLOT(nextVideoDisplay()));
    disconnect(m_vLoader, SIGNAL(uploaded()), this, SLOT(uploaded()));

    /***********/
    connect(m_vLoader, SIGNAL(updateTime(int)), m_parent, SIGNAL(updateTime(int)));
    connect(m_vLoader, SIGNAL(stoped()), m_parent, SIGNAL(stoped()));

    disconnect(m_vLoader, SIGNAL(updateTime(int)), this, SLOT(seqUpdateTime(int)));
    disconnect(this, SIGNAL(updateTime(int)), m_parent, SIGNAL(updateTime(int)));
    disconnect(this, SIGNAL(stoped()), m_parent, SIGNAL(stoped()));

    /******************/
}

void VideoSeq::saveSeq(QString fileName) {
    qDebug() << "slot saveSeq(QString)" << endl;

    connect(this, SIGNAL(uploadVideo(QString*, bool)), m_vLoader, SLOT(uploadVideo(QString*, bool)));
    connect(this, SIGNAL(setStartTime(int)), m_vLoader, SLOT(setStartTime(int)));
    connect(this, SIGNAL(setEndTime(int)), m_vLoader, SLOT(setEndTime(int)));
    connect(m_vLoader, SIGNAL(ended()), this, SLOT(nextVideoWrite()));
    connect(m_vLoader, SIGNAL(uploaded()), this, SLOT(writeUploadedVideo()));

    Mat frame;
    VideoCapture in;
    m_iVideo = 0;

    m_outVideo->open(fileName.toStdString(), CV_FOURCC('M','J','P','G'), 24, Size(500, 400));
    if (m_outVideo->isOpened()) {
        nextVideoWrite();
    }
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

        nextVideoDisplay();
        emit stopVideo();
        emit updateTime(0);
        emit stoped();
    }
}

void VideoSeq::seqPauseVideo() {
    qDebug() << "slot: seqPauseVideo()" << endl;

    emit pauseVideo();
}

void VideoSeq::seqSetTime(int time) {
    qDebug() << "slot: seqSetTime(int)" << endl;

    for (int i = 0; i < m_seq.size(); i++) {
        if (m_seq[i]->endPos < time) {
            qDebug() << i;
            if (!m_seq[i]->isOpened) {
                emit uploadVideo(m_seq[i]->path, false);
                m_seq[i]->isOpened = true;
            }

            emit setTime(time - m_seq[i]->startPos);
            break;
        }
    }
}

void VideoSeq::seqUpdateTime(int time) {
    qDebug() << "slot: seqUpdateTime(int)" << endl;

    emit updateTime(m_pos + time);
    qDebug() << m_pos;
}

void VideoSeq::nextVideoDisplay() {
    qDebug() << "slot: nextVideoDisplay()" << endl;

    if (m_iVideo < m_seq.size()) {
        seqUpdateTime(m_seq[m_iVideo]->startPos);
        emit uploadVideo(m_seq[m_iVideo]->path, false);
    } else {
        emit seqStopVideo();
        disconnect(m_vLoader, SIGNAL(ended()), this, SLOT(nextVideoDisplay()));
        disconnect(m_vLoader, SIGNAL(uploaded()), this, SLOT(uploaded()));
    }
}

void VideoSeq::nextVideoWrite() {
    qDebug() << "slot nextVideoWrite()" << endl;

    if (m_iVideo < m_seq.size()) {
        emit uploadVideo(m_seq[m_iVideo]->path, false);
    } else {
        disconnect(this, SIGNAL(uploadVideo(QString*, bool)), m_vLoader, SLOT(uploadVideo(QString*, bool)));
        disconnect(this, SIGNAL(setStartTime(int)), m_vLoader, SLOT(setStartTime(int)));
        disconnect(this, SIGNAL(setEndTime(int)), m_vLoader, SLOT(setEndTime(int)));
        disconnect(m_vLoader, SIGNAL(ended()), this, SLOT(nextVideoWrite()));
        disconnect(m_vLoader, SIGNAL(uploaded()), this, SLOT(writeUploadedVideo()));

        m_outVideo->release();
        m_iVideo = 0;
    }
}

void VideoSeq::uploaded() {
    qDebug() << "slot: uploaded()" << endl;

    emit setStartTime(m_seq[m_iVideo]->startTime);
    emit setEndTime(m_seq[m_iVideo]->endTime);
    emit setTime(0);
    emit playVideo();

    m_pos = m_seq[m_iVideo]->startPos;

    m_iVideo++;
}

void VideoSeq::writeUploadedVideo() {
    qDebug() << "slot: writeUploadedVideo()" << endl;

    emit setStartTime(m_seq[m_iVideo]->startTime);
    emit setEndTime(m_seq[m_iVideo]->endTime);
    emit writeVideo(m_outVideo);

    m_iVideo++;
}
