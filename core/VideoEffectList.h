#ifndef VIDEO_EFFECT_LIST_H
#define VIDEO_EFFECT_LIST_H

#include <QObject>
#include <QList>

#include "IEffect.h"
#include "VideoEffect.h"

class Core;
class VideoSeq;
namespace cv {
class Mat;
}

class VideoEffectList : public QObject {
    Q_OBJECT
public:
    VideoEffectList(QObject *parent = nullptr);

    VideoSeq *getParent();
    int getStartTime();
    int getEndTime();
    void setStartTime(int);
    void setEndTime(int);
    void handle(cv::Mat&);
public slots:
    void addEffect(QObject*, QString);
    void setEffectStartTime(int);
    void setEffectEndTime(int);
private:
    Core *m_core;
    VideoSeq *m_videoSeq;
    QList<VideoEffect*> m_effects;
    int m_startTime;
    int m_endTime;
};

#endif // VIDEO_EFFECT_LIST_H
