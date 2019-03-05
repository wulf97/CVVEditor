#include <QDebug>

#include "Core.h"

Core::Core(QObject *parent) : QObject(parent) {
    m_VLoader = new VideoLoader(this);
    m_VSeq = new VideoSeq(this);

    /* Проброс сигналов к модулям Core */
    connect(this, SIGNAL(uploadVideo(QString*, bool)), m_VLoader, SLOT(uploadVideo(QString*, bool)));
    connect(this, SIGNAL(unloadVideo()), m_VLoader, SLOT(unloadVideo()));
    connect(this, SIGNAL(playVideo()), m_VLoader, SLOT(playVideo()));
    connect(this, SIGNAL(stopVideo()), m_VLoader, SLOT(stopVideo()));
    connect(this, SIGNAL(pauseVideo()), m_VLoader, SLOT(pauseVideo()));
    connect(this, SIGNAL(setTime(int)), m_VLoader, SLOT(setTime(int)));
    connect(this, SIGNAL(setStartTime(int)), m_VLoader, SLOT(setStartTime(int)));
    connect(this, SIGNAL(setEndTime(int)), m_VLoader, SLOT(setEndTime(int)));
    connect(this, SIGNAL(addToSeq(QString,int,int)), m_VSeq, SLOT(addToSeq(QString,int,int)));
    connect(this, SIGNAL(clearSeq()), m_VSeq, SLOT(clearSeq()));
    connect(this, SIGNAL(loadSeq()), m_VSeq, SLOT(loadSeq()));
    connect(this, SIGNAL(unloadVideo()), m_VSeq, SLOT(unloadSeq()));

    /* Проброс сигналов от модулей Core */
    connect(m_VLoader, SIGNAL(videoLen(int)), this, SIGNAL(videoLen(int)));
    connect(m_VLoader, SIGNAL(updateFrame(QImage*)), this, SIGNAL(updateFrame(QImage*)));
    connect(m_VLoader, SIGNAL(stoped()), this, SIGNAL(stoped()));
    connect(m_VLoader, SIGNAL(updateTime(int)), this, SIGNAL(updateTime(int)));
}

void Core::testSignals() {
    qDebug() << "********** Test core **********" << endl;
    m_VLoader->testSignals();
}

VideoLoader *Core::getVideoLoader() {
    return m_VLoader;
}

VideoSeq *Core::getVideoSeq() {
    return m_VSeq;
}
