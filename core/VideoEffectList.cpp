#include <QDebug>

#include <opencv2/core.hpp>

#include "VideoEffectList.h"
#include "Core.h"
#include "VideoSeq.h"
#include "IEffect.h"

using namespace cv;

VideoEffectList::VideoEffectList(QObject *parent) :
                                         QObject(parent) {
    m_videoSeq = dynamic_cast<VideoSeq*>(parent);
    m_core = m_videoSeq->getParent();
}

VideoSeq *VideoEffectList::getParent() {
    return m_videoSeq;
}

int VideoEffectList::getStartTime() {
    return m_startTime;
}

int VideoEffectList::getEndTime() {
    return m_endTime;
}

void VideoEffectList::setStartTime(int startTime) {
    m_startTime = startTime;
}

void VideoEffectList::setEndTime(int endTime) {
    m_endTime = endTime;
}

void VideoEffectList::handle(Mat &frame) {
    for (int  i = 0; i < m_effects.size(); i++) {
        m_effects[i]->handle(frame);
    }
}

void VideoEffectList::delEffect(QObject *obj) {
    for (int i = 0; i < m_effects.size(); i++) {
        if (m_effects[i] == obj) {
            delete obj;
            m_effects.removeAt(i);
        }
    }
}

void VideoEffectList::addEffect(QObject *obj, QString effectName) {
    qDebug() << "slot: addEffect(QObject*, QString)" << endl;
    VideoEffect *effect = new VideoEffect(this, effectName);
    m_effects.push_back(effect);

    connect(obj, SIGNAL(displayEffectSettings(QBoxLayout*)), effect, SLOT(displayEffectSettings(QBoxLayout*)));
    connect(obj, SIGNAL(delEffect()), effect, SLOT(delEffect()));
}

void VideoEffectList::delEffectList() {
    qDebug() << ",,,,";
    m_core->getVideoSeq()->delEffectList(this);
}

void VideoEffectList::setEffectStartTime(int startTime) {
    qDebug() << "slot: setEffectStartTime(int)" << endl;
    m_startTime = startTime;
}

void VideoEffectList::setEffectEndTime(int endTime) {
    qDebug() << "slot: setEffectEndTime(int)" << endl;
    m_endTime = endTime;
}
