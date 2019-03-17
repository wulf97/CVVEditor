#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QObject>
#include <QDebug>

#include "Viewport.h"
#include "VideoControlBar.h"
#include "VideoCutterList.h"
#include "PluginList.h"

/**
 * @brief Класс GUIManager связывает модули графического интерфейса с внешними модулями.
 *
 * GUIManager принимает сигнылы от внешних модулей и модулей графического интерфейса, а затем перенаправляет их по цепочке.
 */
class GUIManager : public QObject {
    Q_OBJECT
public:
    GUIManager(QObject *parent = nullptr);
    virtual ~GUIManager();

    /**
     * @brief testSignals используется для тестирования сигналов.
     */
    void testSignals();
    /**
     * @brief getViewport используется для получения доступа к Viewport.
     * @return Указатель на Viewport.
     */
    Viewport *getViewport() const;
    /**
     * @brief getVideoControlBar используется для получения доступа к VideoControlBar.
     * @return Указатель на VideoControlBar.
     */
    VideoControlBar *getVideoControlBar() const;
    /**
     * @brief getVideoCutterList используется для получения доступа к VideoCutterList.
     * @return Указатель на VideoCutterList.
     */
    VideoCutterList *getVideoCutterList() const;
    /**
     * @brief getPluginList используется для получения доступа к PluginList.
     * @return Указатель на PluginList.
     */
    PluginList *getPluginList() const;
signals:
    /* Сигналы для внутренних модулей */
    void videoLen(int);
    void updateFrame(QImage*);
    void isStoped();
    void updateTime(int);
    void updateProgress(int);

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
private:
    Viewport *m_viewport;
    VideoControlBar *m_videoControlBar;
    VideoCutterList *m_videoCutterList;
    PluginList *m_pluginList;
};

#endif // GUIMANAGER_H
