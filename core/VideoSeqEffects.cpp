#include <opencv2/core.hpp>

#include "VideoSeqEffects.h"
#include "Core.h"
#include "VideoSeq.h"

using namespace cv;

VideoSeqEffects::VideoSeqEffects(QObject *parent) :
                                 QObject(parent) {
    m_videoSeq = dynamic_cast<VideoSeq*>(parent);
    m_core = m_videoSeq->getParent();
}

int VideoSeqEffects::getStartTime() {
    return m_startTime;
}

int VideoSeqEffects::getEndTime() {
    return m_endTime;
}

void VideoSeqEffects::setStartTime(int startTime) {
    m_startTime = startTime;
}

void VideoSeqEffects::setEndTime(int endTime) {
    m_endTime = endTime;
}

void VideoSeqEffects::addEffect(IEffect *effect) {
    m_effects.push_back(effect);
}

void VideoSeqEffects::handle(Mat &frame) {
    for (int  i = 0; i < m_effects.size(); i++) {
        m_effects[i]->handle(frame);
    }
}
