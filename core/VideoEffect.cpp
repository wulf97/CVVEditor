#include <QDebug>
#include <QHBoxLayout>
#include <QWidget>

#include "VideoEffect.h"
#include "VideoSeq.h"
#include "Core.h"
#include "VideoEffectList.h"

using namespace cv;

VideoEffect::VideoEffect(QObject *parent, QString effectName) :
                         QObject(parent) {
    m_videoEffectList = dynamic_cast<VideoEffectList*>(parent);
    m_core = m_videoEffectList->getParent()->getParent();
    m_effect = m_core->getPluginManager()->createByName(effectName);
}

void VideoEffect::handle(Mat &frame) {
    m_effect->handle(frame);
}

void VideoEffect::displayEffectSettings(QBoxLayout *layout) {
    qDebug() << "slot: displayEffectSettings(QBoxLayout*)" << endl;
    QLayoutItem *item;
    QWidget *w;
    while((item = layout->itemAt(0))) {
        w = item->widget();
        layout->removeItem(item);
        w->hide();
        delete item;
        layout->update();
    }

    m_effect->display(layout);
}

void VideoEffect::delEffect() {
    m_videoEffectList->delEffect(this);
}
