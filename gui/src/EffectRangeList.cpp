#include "EffectRangeList.h"
#include "GUIManager.h"

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
