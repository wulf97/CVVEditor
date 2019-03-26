#include "GUIManager.h"

GUIManager::GUIManager(QWidget *parent) :
                       QWidget(parent) {
    m_viewport = new Viewport(this);
    m_videoControlBar = new VideoControlBar(this);
    m_effectRangeList = new EffectRangeList(this);
    m_videoCutterList = new VideoCutterList(this);
    m_pluginList = new PluginList(this);

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

    connect(m_videoCutterList, SIGNAL(uploadVideo(QString*, bool)), SIGNAL(uploadVideo(QString*, bool)));
    connect(m_videoCutterList, SIGNAL(unloadVideo()), SIGNAL(unloadVideo()));
    connect(m_videoCutterList, SIGNAL(setStartTime(int)), SIGNAL(setStartTime(int)));
    connect(m_videoCutterList, SIGNAL(setEndTime(int)), SIGNAL(setEndTime(int)));
    connect(m_videoCutterList, SIGNAL(addToSeq(QString,int,int)), SIGNAL(addToSeq(QString,int,int)));
    connect(m_videoCutterList, SIGNAL(clearSeq()), SIGNAL(clearSeq()));
    connect(m_videoCutterList, SIGNAL(loadSeq()), SIGNAL(loadSeq()));
    connect(m_videoCutterList, SIGNAL(unloadSeq()), SIGNAL(unloadSeq()));
    connect(m_videoCutterList, SIGNAL(saveSeq(QString)), SIGNAL(saveSeq(QString)));

    connect(m_videoCutterList, SIGNAL(sendLengthOfVideo(int)), m_videoControlBar, SLOT(setEndTime(int)));
    connect(m_videoCutterList, SIGNAL(sendCurrentPositionSlider(int)), m_videoControlBar, SLOT(slotSetSliderPosition(int)));
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
