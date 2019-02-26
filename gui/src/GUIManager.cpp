#include "GUIManager.h"

GUIManager::GUIManager(QObject *parent) : QObject(parent) {
    m_viewport = new Viewport();
    m_videoControlBar = new VideoControlBar();
    m_videoCutterList = new VideoCutterList();
    m_pluginList = new PluginList();

    /* Проброс сигналов к модулям GUIManager */
    connect(this, SIGNAL(updateFrame(QImage*)), m_viewport, SLOT(updateFrame(QImage*)));
    connect(this, SIGNAL(stoped()), m_videoControlBar, SLOT(stoped()));
    connect(this, SIGNAL(videoLen(int)), m_videoCutterList, SLOT(videoLen(int)));

    /* Проброс сигналов от модулей GUIManager */
    connect(m_videoControlBar, SIGNAL(playVideo()), SIGNAL(playVideo()));
    connect(m_videoControlBar, SIGNAL(stopVideo()), SIGNAL(stopVideo()));
    connect(m_videoControlBar, SIGNAL(pauseVideo()), SIGNAL(pauseVideo()));
    connect(m_videoControlBar, SIGNAL(setTime(int)), SIGNAL(setTime(int)));

    connect(m_videoCutterList, SIGNAL(uploadVideo(QString*, bool)), SIGNAL(uploadVideo(QString*, bool)));
    connect(m_videoCutterList, SIGNAL(setStartTime(int)), SIGNAL(setStartTime(int)));
    connect(m_videoCutterList, SIGNAL(setEndTime(int)), SIGNAL(setEndTime(int)));
}

void GUIManager::testSignals() {
    qDebug() << "********** Test gui **********" << endl;
    m_videoControlBar->testSignals();
}

GUIManager::~GUIManager() {
    delete m_viewport;
    delete m_videoControlBar;
    delete m_videoCutterList;
    delete m_pluginList;
}

Viewport *GUIManager::getViewport() const {
    return m_viewport;
}

VideoControlBar *GUIManager::getVideoControlBar() const {
    return m_videoControlBar;
}

VideoCutterList *GUIManager::getVideoCutterList() const {
    return m_videoCutterList;
}

PluginList *GUIManager::getPluginList() const {
    return m_pluginList;
}
