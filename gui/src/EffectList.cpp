#include "ui_EffectList.h"
#include "EffectList.h"
#include "GUIManager.h"

EffectList::EffectList(QWidget *parent) :
               QWidget(parent),
               ui(new Ui::EffectList) {
    m_parent = dynamic_cast<GUIManager*>(parent);
    ui->setupUi(this);
}

EffectList::~EffectList() {
    delete ui;
}

void EffectList::setConnection() {
    /* Подключение сигналов */
}
