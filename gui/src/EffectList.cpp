#include "ui_EffectList.h"
#include "EffectList.h"
#include "GUIManager.h"
#include "Effect.h"

EffectList::EffectList(QWidget *parent) :
               QWidget(parent),
               ui(new Ui::EffectList) {
    m_parent = dynamic_cast<PluginList*>(parent);
    ui->setupUi(this);
    connect(ui->addBtn, SIGNAL(released()), this, SLOT(addNewEffect()));
}

EffectList::~EffectList() {
    delete ui;
}

PluginList *EffectList::getParent() {
    return m_parent;
}

void EffectList::setConnection() {
    /* Подключение сигналов */
}

void EffectList::setEffectList(QString item)
{
    ui->comboBox->addItem(item);
}

void EffectList::addNewEffect()
{
    Effect *effect = new Effect(this, ui->comboBox->currentText());
    listOfEffectsWidget.append(effect);
    ui->effectListLayout->addWidget(effect);

}
