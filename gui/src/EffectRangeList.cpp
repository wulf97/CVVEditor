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
}

EffectRange *EffectRangeList::addNewEffectRange(int num)
{
    endTimeOfVideo = m_parent->getVideoCutterList()->getLengthFullVideo();
        EffectRange* effectRange = new EffectRange(this, endTimeOfVideo);
        if (!listOfEffectRangeWidget.empty()) {
            effectRange->setMinimumValue(listOfEffectRangeWidget[listOfEffectRangeWidget.size() - 1]->getUpperValue());
        }
        connect(effectRange, SIGNAL(updateStartTimeNextRange(int,int)), this, SLOT(updateStartTimeNextRange(int,int)));
        effectRange->setNumInList(num);
        listOfEffectRangeWidget.append(effectRange);
        layout->addWidget(effectRange);
        this->setLayout(layout);
        return effectRange;
}

void EffectRangeList::updateEndTime(int time)
{
    endTimeOfVideo = time;
    for(int i = 0; i < listOfEffectRangeWidget.size(); i++) {
         listOfEffectRangeWidget[i]->updateEndTime(endTimeOfVideo);
     }
}

void EffectRangeList::deleteEffectRange(int num)
{
    for (auto i : listOfEffectRangeWidget) {
        EffectRange* p = dynamic_cast<EffectRange*>(i);
        if (p->getNumInList() == num) {
            delete p;
            listOfEffectRangeWidget.removeOne(p);
        }
    }
}

void EffectRangeList::updateStartTimeNextRange(int time, int num)
{
    for(int i = 0; i < listOfEffectRangeWidget.size(); i++) {
        if (listOfEffectRangeWidget[i]->getNumInList() == num && listOfEffectRangeWidget[i] != listOfEffectRangeWidget[listOfEffectRangeWidget.size() - 1]) {
            listOfEffectRangeWidget[i+1]->setMinimumValue(time);
        }
     }
}


