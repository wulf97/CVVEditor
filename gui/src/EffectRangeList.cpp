#include "EffectRangeList.h"
#include "GUIManager.h"
#include <EffectRange.h>

EffectRangeList::EffectRangeList(QWidget *parent) :
                                 QWidget(parent) {
    m_parent = dynamic_cast<GUIManager*>(parent);

    setConnection(); 
}

EffectRangeList::~EffectRangeList() {

}

void EffectRangeList::setConnection() {
    /* Подключение сигналов */
}

void EffectRangeList::addNewEffectRange()
{
    endTimeOfVideo = m_parent->getVideoCutterList()->getLengthFullVideo();
    EffectRange* effectRange = new EffectRange(this, endTimeOfVideo);
    listOfEffectRangeWidget.append(effectRange);
    layout->addWidget(effectRange);
    this->setLayout(layout);
}

void EffectRangeList::updateEndTime(int time)
{
    endTimeOfVideo = time;
    for(int i = 0; i < listOfEffectRangeWidget.size(); i++) {
        listOfEffectRangeWidget[i]->updateEndTime(endTimeOfVideo);
    }

}


