#ifndef VIDEO_SEQ_EFFECT_H
#define VIDEO_SEQ_EFFECT_H

#include <QObject>

//#include "VideoSeqEffectsWrap.h"
#include "IEffect.h"

class VideoSeqEffectsWrap;
class Core;
namespace cv {
class Mat;
}

class VideoSeqEffect : public QObject {
    Q_OBJECT
public:
    VideoSeqEffect(QObject *parent, QString);

    void handle(cv::Mat&);
public slots:
    void displayEffectSettings(QBoxLayout*);
private:
    Core *m_core;
    VideoSeqEffectsWrap *m_videoSeqEffectsWrap;
    IEffect *m_effect;
};

#endif // VIDEO_SEQ_EFFECT_H
