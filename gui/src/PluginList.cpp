#include <QDebug>
#include <QLayout>
#include <QPushButton>

#include "ui_PluginList.h"
#include "PluginList.h"
#include <GUIManager.h>
#include <EffectList.h>
#include <EffectRange.h>


PluginList::PluginList(QWidget *parent) :
                       QWidget(parent),
                       ui(new Ui::PluginList) {
    ui->setupUi(this);
    m_parent = dynamic_cast<GUIManager*>(parent);
    connect(ui->addBtn, SIGNAL(released()), this, SLOT(addEffectList()));
    connect(ui->addBtn, SIGNAL(released()), m_parent, SIGNAL(getEffectsList()));

    connect(this, SIGNAL(deleteEffectRange(int)), m_parent->getEffectRangeList(), SLOT(deleteEffectRange(int)));
    connect(this, SIGNAL(addNewEffectRange(int)), m_parent->getEffectRangeList(), SLOT(addNewEffectRange(int)));

    connect(this, SIGNAL(addEffectList(QObject*,int,int)), m_parent, SIGNAL(addEffectList(QObject*,int,int)));
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
    effectList->setNumInList(listOfEffectList.size());
    EffectRange* effectRange = m_parent->getEffectRangeList()->addNewEffectRange(listOfEffectList.size());
    connect(effectRange, SIGNAL(setStartTime(int)),effectList, SLOT(setStartTimeRange(int)));
    connect(effectRange, SIGNAL(setEndTime(int)), effectList, SLOT(setStartEndRange(int)));

    listOfEffectList.append(effectList);
    ui->pluginListLayout->addWidget(effectList);
    emit addEffectList(effectList, 0, m_parent->getVideoCutterList()->getLengthFullVideo());
}

void PluginList::setEffectsToEffectList(QStringList list)
{
        for (int k = 0; k < list.size(); k ++) {
            listOfEffectList[listOfEffectList.size() - 1]->setEffectList(list[k]);
        }
}

void PluginList::deleteEffectList(int num)
{
    deleteEffectRange(num);
    for (auto i : listOfEffectList) {
        EffectList* p = dynamic_cast<EffectList*>(i);
        if (p->getNumInList() == num) {
            delete p;
            listOfEffectList.removeOne(p);
        }
    }

}
