#include <QDebug>

#include "Core.h"

Core::Core(QObject *parent) : QObject(parent) {
    m_VLoader = new VideoLoader(this);

    /* Проброс сигналов к модулям Core */
    connect(this, SIGNAL(uploadVideo(QString*)), m_VLoader, SLOT(uploadVideo(QString*)));
    connect(this, SIGNAL(playVideo()), m_VLoader, SLOT(playVideo()));
    connect(this, SIGNAL(stopVideo()), m_VLoader, SLOT(stopVideo()));
    connect(this, SIGNAL(pauseVideo()), m_VLoader, SLOT(pauseVideo()));

    /* Проброс сигналов от модулей Core */
    connect(m_VLoader, SIGNAL(videoLen(int)), this, SIGNAL(videoLen(int)));
    connect(m_VLoader, SIGNAL(updateFrame(QImage*)), this, SIGNAL(updateFrame(QImage*)));
    connect(m_VLoader, SIGNAL(stoped()), this, SIGNAL(stoped()));
}
