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
}

PluginList::~PluginList() {
    delete ui;
}

void PluginList::addEffectList()
{
    EffectList* effectList = new EffectList(this);
    listOfEffectList.append(effectList);
    ui->pluginListLayout->addWidget(effectList);
}
