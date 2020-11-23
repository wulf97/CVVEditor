#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QBoxLayout>

//#include "PluginManager.h"
//#include "VideoLoader.h"
//#include "VideoSeq.h"

class CvvINode;
class CvvINodeFactory;
class NodeControl;

class Core : public QObject {
    Q_OBJECT
public:
    Core(QObject *parent = nullptr);
    ~Core();

//    PluginManager *getPluginManager();
//    VideoLoader *getVideoLoader();
//    VideoSeq *getVideoSeq();
    CvvINode *createNode(QString);
public slots:
//    void getEffectsList();
    void displaySettings(CvvINode*);

    NodeControl *getController(CvvINode*) const;
    void makeGlobal(NodeControl*);
    void setGlobalTime(int);
signals:
    void update();

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
    QVector<CvvINodeFactory*> m_nodeFactory;
    QVector<NodeControl*> m_nodeControl;
    int m_globalTime = 0;
};

#endif // CORE_H
