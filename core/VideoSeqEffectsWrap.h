#ifndef VIDEO_SEQ_EFFECTS_WRAP_H
#define VIDEO_SEQ_EFFECTS_WRAP_H

#include <QObject>
#include <QList>

#include "IEffect.h"
#include "VideoSeqEffect.h"

class Core;
class VideoSeq;
namespace cv {
class Mat;
}

class VideoSeqEffectsWrap : public QObject {
    Q_OBJECT
public:
    VideoSeqEffectsWrap(QObject *parent = nullptr);

    VideoSeq *getParent();
    int getStartTime();
    int getEndTime();
    void setStartTime(int);
    void setEndTime(int);
    void handle(cv::Mat&);
public slots:
    void addEffect(QObject*, QString);
private:
    Core *m_core;
    VideoSeq *m_videoSeq;
    QList<VideoSeqEffect*> m_effects;
    int m_startTime;
    int m_endTime;
};

#endif // VIDEO_SEQ_EFFECTS_WRAP_H
