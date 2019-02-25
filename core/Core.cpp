#include <QDebug>

#include "Core.h"

Core::Core(QObject *parent) : QObject(parent) {
    m_VLoader = new VideoLoader(this);

    /* Проброс сигналов к модулям Core */
    connect(this, SIGNAL(uploadVideo(QString*, bool)), m_VLoader, SLOT(uploadVideo(QString*, bool)));
    connect(this, SIGNAL(playVideo()), m_VLoader, SLOT(playVideo()));
    connect(this, SIGNAL(stopVideo()), m_VLoader, SLOT(stopVideo()));
    connect(this, SIGNAL(pauseVideo()), m_VLoader, SLOT(pauseVideo()));
    connect(this, SIGNAL(setTime(int)), m_VLoader, SLOT(setTime(int)));
    connect(this, SIGNAL(setStartTime(int)), m_VLoader, SLOT(setStartTime(int)));
    connect(this, SIGNAL(setEndTime(int)), m_VLoader, SLOT(setEndTime(int)));

    /* Проброс сигналов от модулей Core */
    connect(m_VLoader, SIGNAL(videoLen(int)), this, SIGNAL(videoLen(int)));
    connect(m_VLoader, SIGNAL(updateFrame(QImage*)), this, SIGNAL(updateFrame(QImage*)));
    connect(m_VLoader, SIGNAL(stoped()), this, SIGNAL(stoped()));
}

void Core::testSignals() {
    qDebug() << "********** Test core **********" << endl;
    m_VLoader->testSignals();
}
