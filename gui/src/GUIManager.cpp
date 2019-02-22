#include "GUIManager.h"

GUIManager::GUIManager(QObject *parent) : QObject(parent) {
    m_viewport = new Viewport();
    m_videoControlBar = new VideoControlBar();
    m_videoCutterList = new VideoCutterList();
    m_pluginList = new PluginList();
}

GUIManager::~GUIManager() {
    delete m_viewport;
    delete m_videoControlBar;
    delete m_videoCutterList;
    delete m_pluginList;
}

void GUIManager::setCore(QObject *core) {
    m_core = core;

    /* Проброс сигналов к модулям GUIManager */
    connect(this, SIGNAL(updateFrame(QImage*)), m_viewport, SLOT(updateFrame(QImage*)));
    connect(this, SIGNAL(stoped()), m_videoControlBar, SLOT(stoped()));
    connect(this, SIGNAL(videoLen(int)), m_videoCutterList, SIGNAL(videoLen(int)));

    /* Проброс сигналов от модулей GUIManager */
    connect(m_videoControlBar, SIGNAL(playVideo()), SIGNAL(playVideo()));
    connect(m_videoControlBar, SIGNAL(stopVideo()), SIGNAL(stopVideo()));
    connect(m_videoControlBar, SIGNAL(pauseVideo()), SIGNAL(pauseVideo()));
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
