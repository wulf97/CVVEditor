#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QWidget>
#include <QDebug>

#include "Viewport.h"
#include "VideoControlBar.h"
#include "VideoCutterList.h"
#include "PluginList.h"
#include "EffectRangeList.h"
#include "EffectSettings.h"


/**
 * @brief Класс GUIManager связывает модули графического интерфейса с внешними модулями.
 *
 * GUIManager принимает сигнылы от внешних модулей и модулей графического интерфейса, а затем перенаправляет их по цепочке.
 */
class GUIManager : public QWidget {
    Q_OBJECT
public:
    GUIManager(QWidget *parent = nullptr);
    virtual ~GUIManager();

    void testSignals();
    Viewport *getViewport() const;
    VideoControlBar *getVideoControlBar() const;
    VideoCutterList *getVideoCutterList() const;
    EffectRangeList *getEffectRangeList() const;
    PluginList *getPluginList() const;
    EffectSettings *getEffectSettings() const;
signals:
    /* Сигналы для внутренних модулей */
    void videoLen(int);
    void updateFrame(QImage*);
    void isStoped();
    void updateTime(int);
    void updateProgress(int);
    void effectsList(QStringList);

    /* Сигналы для внешних модулей */
    void uploadVideo(QString*, bool);
    void unloadVideo();
    void playVideo();
    void stopVideo();
    void pauseVideo();
    void setTime(int);
    void setStartTime(int);
    void setEndTime(int);
    void addToSeq(QString, int, int);
    void clearSeq();
    void loadSeq();
    void unloadSeq();
    void saveSeq(QString);
    void getEffectsList();
    void addEffectWrap(QObject*, int, int);

private:
    Viewport *m_viewport;
    VideoControlBar *m_videoControlBar;
    VideoCutterList *m_videoCutterList;
    EffectRangeList *m_effectRangeList;
    PluginList *m_pluginList;
    EffectSettings *m_effectSettings;
};

#endif // GUIMANAGER_H
