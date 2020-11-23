#include "GUIManager.h"
#include "PluginList.h"
#include "PluginSettings.h"

GUIManager::GUIManager(QWidget *parent) :
                       QWidget(parent) {
    m_viewport = new Viewport(this);
    m_videoControlBar = new VideoControlBar(this);
    m_effectRangeList = new EffectRangeList(this);
    m_videoCutterList = new VideoCutterList(this);
    m_pluginList = new PluginList(this);
    m_effectSettings = new EffectSettings(this);
    m_effectViewport = new EffectViewport(this);
    m_nodeEditor = new NodeEditor(this);
    m_pluginSettings = new PluginSettings(this);
    //m_effectList = new EffectList(this);

    m_pluginSettings->metaObject();


    /* Проброс сигналов к модулям GUIManager */
    connect(this, SIGNAL(updateFrame(QImage*)), m_viewport, SLOT(updateFrame(QImage*)));
    connect(this, SIGNAL(isStoped()), m_videoControlBar, SLOT(isStoped()));
    connect(this, SIGNAL(updateTime(int)), m_videoControlBar, SLOT(updateTime(int)));
    connect(this, SIGNAL(videoLen(int)), m_videoCutterList, SLOT(videoLen(int)));

    /* Проброс сигналов от модулей GUIManager */
    connect(m_videoControlBar, SIGNAL(playVideo()), SIGNAL(playVideo()));
    connect(m_videoControlBar, SIGNAL(stopVideo()), SIGNAL(stopVideo()));
    connect(m_videoControlBar, SIGNAL(pauseVideo()), SIGNAL(pauseVideo()));
    connect(m_videoControlBar, SIGNAL(setTime(int)), SIGNAL(setTime(int)));

    connect(m_videoControlBar, SIGNAL(sendTime(int)), m_videoCutterList, SLOT(sendCurrentTimeToCutter(int)));
}

void GUIManager::testSignals() {
    qDebug() << "********** Test gui **********" << endl;
    m_videoControlBar->testSignals();
}

GUIManager::~GUIManager() {
    delete m_viewport;
    delete m_videoControlBar;
    delete m_videoCutterList;
    delete m_effectRangeList;
    delete m_pluginList;
    delete m_nodeEditor;
    delete m_pluginSettings;
    //delete m_effectList;
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

EffectRangeList *GUIManager::getEffectRangeList() const {
    return m_effectRangeList;
}

PluginList *GUIManager::getPluginList() const {
    return m_pluginList;
}

EffectSettings *GUIManager::getEffectSettings() const {
    return m_effectSettings;
}

EffectViewport *GUIManager::getEffectViewport() const {
    return m_effectViewport;
}

NodeEditor *GUIManager::getNodeEditor() const {
    return m_nodeEditor;
}

PluginSettings *GUIManager::getPluginSettings() const {
    return m_pluginSettings;
}

void GUIManager::displaySettings(CvvINode *node) {
    m_pluginSettings->displaySettings(node);
}

void GUIManager::display(CvvINode *node) {

}
