#include <QDebug>

#include <opencv2/core.hpp>

#include "VideoSeqEffectsWrap.h"
#include "Core.h"
#include "VideoSeq.h"
#include "IEffect.h"

using namespace cv;

VideoSeqEffectsWrap::VideoSeqEffectsWrap(QObject *parent) :
                                         QObject(parent) {
    m_videoSeq = dynamic_cast<VideoSeq*>(parent);
    m_core = m_videoSeq->getParent();
}

VideoSeq *VideoSeqEffectsWrap::getParent() {
    return m_videoSeq;
}

int VideoSeqEffectsWrap::getStartTime() {
    return m_startTime;
}

int VideoSeqEffectsWrap::getEndTime() {
    return m_endTime;
}

void VideoSeqEffectsWrap::setStartTime(int startTime) {
    m_startTime = startTime;
}

void VideoSeqEffectsWrap::setEndTime(int endTime) {
    m_endTime = endTime;
}

void VideoSeqEffectsWrap::addEffect(QObject *obj, QString effectName) {
    qDebug() << "slot: addEffect(QObject*, QString)" << endl;
    VideoSeqEffect *effect = new VideoSeqEffect(this, effectName);
    m_effects.push_back(effect);

    connect(obj, SIGNAL(displayEffectSettings(QBoxLayout*)), effect, SLOT(displayEffectSettings(QBoxLayout*)));
}

void VideoSeqEffectsWrap::handle(Mat &frame) {
    for (int  i = 0; i < m_effects.size(); i++) {
        m_effects[i]->handle(frame);
    }
}
