#include <QDebug>

#include "Core.h"
#include "IEffect.h"

#include "CvvINode.h"
#include "CvvINodePort.h"
#include "TestNode.h"

Core::Core(QObject *parent) : QObject(parent) {
    /*******/
    //TestNode node1(this);
//    CvvINodeFuctory *f1 = new TestNodeFactory(this);

//    CvvINode *node1 = f1->addNode();
//    CvvINode *node2 = f1->addNode();

//    if (node1) {
//        connect(this, SIGNAL(update()), node1, SLOT(update()));
//    }

//    if (node2) {
//        connect(this, SIGNAL(update()), node2, SLOT(update()));
//    }

//    qDebug() << f1->getName();
//    qDebug() << node1->getItemName();
//    qDebug() << node2->getItemName();

//    emit update();
    m_nodeFactory.append(new TestNodeFactory(this));



    QStringList effects;
    m_pManager = new PluginManager(this);
    m_VLoader = new VideoLoader(this);
    m_VSeq = new VideoSeq(this);

    m_pManager->load();
}

PluginManager *Core::getPluginManager() {
    return m_pManager;
}

VideoLoader *Core::getVideoLoader() {
    return m_VLoader;
}

VideoSeq *Core::getVideoSeq() {
    return m_VSeq;
}

CvvINode *Core::createNode(QString nodeName) {
    for (int i = 0; i < m_nodeFactory.size(); i++) {
        if (m_nodeFactory.at(i)->getName() == nodeName) {
            CvvINode *node = m_nodeFactory.at(i)->createNode();
            m_node.append(node);
            return node;
        }
    }

    return nullptr;
}

//void Core::displaySettings(QString effectName, QBoxLayout *layout) {
//    qDebug() << "slot displaySettings(QString, QBoxLayout*)" << endl;
//    for (int i = 0; i < m_pManager->size(); i++) {
//        if (effectName == m_pManager->get(i)->getName()) {
//            m_pManager->get(i)->display(layout);
//        }
//    }
//}

void Core::getEffectsList() {
    QStringList effects;
    for (int i = 0; i < m_pManager->size(); i++) {
        effects.push_back(m_pManager->get(i));
    }

    emit effectsList(effects);
}
