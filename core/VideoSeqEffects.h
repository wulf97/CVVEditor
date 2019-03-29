#ifndef VIDEOSEQEFFECTS_H
#define VIDEOSEQEFFECTS_H

#include <QObject>
#include <QList>

#include "IEffect.h"

class Core;
class VideoSeq;
namespace cv {
class Mat;
}

class VideoSeqEffects : public QObject {
    Q_OBJECT
public:
    VideoSeqEffects(QObject *parent = nullptr);

    int getStartTime();
    int getEndTime();
    void setStartTime(int);
    void setEndTime(int);
    void addEffect(IEffect*);
    void handle(cv::Mat&);
private:
    Core *m_core;
    VideoSeq *m_videoSeq;
    QList<IEffect*> m_effects;
    int m_startTime;
    int m_endTime;
};

#endif // VIDEOSEQEFFECTS_H
