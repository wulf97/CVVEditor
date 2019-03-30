#include "VideoSeqEffect.h"
#include "VideoSeq.h"
#include "Core.h"
#include "VideoSeqEffectsWrap.h"

using namespace cv;

VideoSeqEffect::VideoSeqEffect(QObject *parent, QString effectName) :
                               QObject(parent) {
    m_videoSeqEffectsWrap = dynamic_cast<VideoSeqEffectsWrap*>(parent);
    m_core = m_videoSeqEffectsWrap->getParent()->getParent();
    m_effect = m_core->getPluginManager()->createByName(effectName);
}

void VideoSeqEffect::handle(Mat &frame) {
    m_effect->handle(frame);
}

void VideoSeqEffect::displayEffectSettings(QBoxLayout *layout) {
    m_effect->display(layout);
}
