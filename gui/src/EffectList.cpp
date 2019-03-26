#include "ui_EffectList.h"
#include "EffectList.h"
#include "GUIManager.h"
#include <Effect.h>
EffectList::EffectList(QWidget *parent) :
               QWidget(parent),
               ui(new Ui::EffectList) {
    m_parent = dynamic_cast<GUIManager*>(parent);
    ui->setupUi(this);
    connect(ui->addBtn, SIGNAL(released()), this, SLOT(addNewEffect(QString)));
}

EffectList::~EffectList() {
    delete ui;
}

void EffectList::setConnection() {
    /* Подключение сигналов */
}

void EffectList::setEffectList(QString item)
{
    ui->comboBox->addItem(item);
}

void EffectList::addNewEffect(QString)
{
    Effect *effect = new Effect(this);
}
