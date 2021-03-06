#ifndef CORE_H
#define CORE_H

#include <QObject>

#include "PluginManager.h"
#include "VideoLoader.h"
#include "VideoSeq.h"


class QBoxLayout;

class Core : public QObject {
    Q_OBJECT
public:
    Core(QObject *parent = nullptr);

    PluginManager *getPluginManager();
    VideoLoader *getVideoLoader();
    VideoSeq *getVideoSeq();
public slots:
    void getEffectsList();
signals:
    /* Сигналы для внутренних модулей */
    void addViewport(QObject*);
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
    void addEffectList(QObject*, int, int);

    /* Сигналы для внешних модулей */
    void videoLen(int);
    void updateFrame(QImage*);
    void isStoped();
    void updateTime(int);
    void ended();
    void updateProgress(int);
    void effectsList(QStringList);
private:
    PluginManager *m_pManager;
    VideoLoader *m_VLoader;
    VideoSeq *m_VSeq;
};

#endif // CORE_H
