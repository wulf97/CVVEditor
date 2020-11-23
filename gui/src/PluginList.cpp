#include <QDebug>
#include <QLayout>
#include <QPushButton>

#include "GUIManager.h"
//#include <EffectList.h>
//#include <EffectRange.h>
#include "ui_PluginList.h"
#include "PluginList.h"
#include "CvvINode.h"


PluginList::PluginList(QWidget *parent) :
                       QWidget(parent),
                       ui(new Ui::PluginList) {
    ui->setupUi(this);
    qDebug() << "kkkkkk";
//    m_parent = dynamic_cast<GUIManager*>(parent);
//    m_settingsLayout = ui->settingsLayout;




//    connect(ui->addBtn, SIGNAL(released()), this, SLOT(addEffectList()));
//    connect(ui->addBtn, SIGNAL(released()), m_parent, SIGNAL(getEffectsList()));

//    connect(this, SIGNAL(deleteEffectRange(int)), m_parent->getEffectRangeList(), SLOT(deleteEffectRange(int)));
//    connect(this, SIGNAL(addNewEffectRange(int)), m_parent->getEffectRangeList(), SLOT(addNewEffectRange(int)));

//    connect(this, SIGNAL(addEffectList(QObject*,int,int)), m_parent, SIGNAL(addEffectList(QObject*,int,int)));
}

PluginList::~PluginList() {
    delete ui;
}

void PluginList::blaa() {
    qDebug() << "bla";
}

//GUIManager *PluginList::getParent() {
//    return m_parent;
//}

/*
void PluginList::displaySettings(CvvINode *node) {
    qDebug() << "dffg";
//    if (node) {
//        for (int i = 0; i < m_settingsLayout->count(); i++) {
//            m_settingsLayout->itemAt(i)->widget()->setParent(nullptr);
//            delete m_settingsLayout->itemAt(i);
//        }

//        for (int i = 0; i < m_displayLayout->count(); i++) {
//            m_displayLayout->itemAt(i)->widget()->setParent(nullptr);
//            delete m_displayLayout->itemAt(i);
//        }

//        m_label->setText(node->getItemName() + QString::number(getController(node)->getDuration()));

//        node->displaySettings(m_settingsLayout);
//        node->display(m_settingsLayout);
//    }
}
*/
