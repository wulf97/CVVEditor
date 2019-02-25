#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QObject>
#include <QDebug>

#include "Viewport.h"
#include "VideoControlBar.h"
#include "VideoCutterList.h"
#include "PluginList.h"

class GUIManager : public QObject {
    Q_OBJECT
public:
    GUIManager(QObject *parent = nullptr);
    virtual ~GUIManager();

    void testSignals();

    Viewport *getViewport() const;
    VideoControlBar *getVideoControlBar() const;
    VideoCutterList *getVideoCutterList() const;
    PluginList *getPluginList() const;
signals:
    /* Сигналы для внутренних модулей */
    void videoLen(int);
    void updateFrame(QImage*);
    void stoped();

    /* Сигналы для внешних модулей */
    void uploadVideo(QString*, bool);
    void playVideo();
    void stopVideo();
    void pauseVideo();
    void setTime(int);
    void setStartTime(int);
    void setEndTime(int);
private:
    Viewport *m_viewport;
    VideoControlBar *m_videoControlBar;
    VideoCutterList *m_videoCutterList;
    PluginList *m_pluginList;
};

#endif // GUIMANAGER_H
