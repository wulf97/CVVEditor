#include <QDebug>
#include <QPushButton>

#include "PluginSettings.h"
#include "CvvINode.h"

PluginSettings::PluginSettings(QWidget *parent) :
                               QWidget(parent) {
    m_settingsLayout = new QVBoxLayout(this);
//    QPushButton *btn = new QPushButton(this);

//    mainLayout->addWidget(btn);

    setLayout(m_settingsLayout);
}

PluginSettings::~PluginSettings() {

}

void PluginSettings::displaySettings(CvvINode *node) {
    if (node) {
        for (int i = 0; i < m_settingsLayout->count(); i++) {
            m_settingsLayout->itemAt(i)->widget()->setParent(nullptr);
            delete m_settingsLayout->itemAt(i);
        }

//        for (int i = 0; i < m_displayLayout->count(); i++) {
//            m_displayLayout->itemAt(i)->widget()->setParent(nullptr);
//            delete m_displayLayout->itemAt(i);
//        }

//        m_label->setText(node->getItemName() + QString::number(getController(node)->getDuration()));

//        node->displaySettings(m_settingsLayout);
        node->displaySettings(m_settingsLayout);
    }
}
