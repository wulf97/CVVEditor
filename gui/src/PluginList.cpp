#include <QDebug>
#include <QLayout>
#include <QPushButton>

#include "ui_PluginList.h"
#include "PluginList.h"
#include <GUIManager.h>
#include <EffectList.h>


PluginList::PluginList(QWidget *parent) :
                       QWidget(parent),
                       ui(new Ui::PluginList) {
    ui->setupUi(this);
    m_parent = dynamic_cast<GUIManager*>(parent);
    connect(ui->addBtn, SIGNAL(released()), m_parent->getEffectRangeList(), SLOT(addNewEffectRange()));
    connect(ui->addBtn, SIGNAL(released()), this, SLOT(addEffectList()));
    connect(ui->addBtn, SIGNAL(released()), m_parent, SIGNAL(getEffectsList()));
}

PluginList::~PluginList() {
    delete ui;
}

GUIManager *PluginList::getParent() {
    return m_parent;
}

void PluginList::addEffectList()
{
    EffectList* effectList = new EffectList(this);
    listOfEffectList.append(effectList);
    ui->pluginListLayout->addWidget(effectList);
}

void PluginList::setEffectsToEffectList(QStringList list)
{
    qDebug()<<"EEEEEEEEEEEEEEEEEEEE";
    for (int i = 0; i < listOfEffectList.size(); i++) {
        for (int k = 0; k < list.size(); k ++) {
            listOfEffectList[i]->setEffectList(list[k]);
        }
    }
}
