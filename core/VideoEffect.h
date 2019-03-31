#ifndef VIDEO_EFFECT_H
#define VIDEO_EFFECT_H

#include <QObject>

//#include "VideoSeqEffectsWrap.h"
#include "IEffect.h"

class VideoEffectList;
class Core;
namespace cv {
class Mat;
}

class VideoEffect : public QObject {
    Q_OBJECT
public:
    VideoEffect(QObject *parent, QString);

    void handle(cv::Mat&);
public slots:
    void displayEffectSettings(QBoxLayout*);
private:
    Core *m_core;
    VideoEffectList *m_videoEffectList;
    IEffect *m_effect;
};

#endif // VIDEO_EFFECT_H
