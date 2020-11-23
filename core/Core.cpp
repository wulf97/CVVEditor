#include <QDebug>
#include <QPluginLoader>
#include <QDir>

#include "Core.h"
//#include "IEffect.h"

#include "CvvINode.h"
#include "CvvINodePort.h"
#include "NodeControl.h"

//#include "TestNode.h"
//#include "VideoNode.h"
//#include "ViewportNode.h"
//#include "CombineNode.h"
//#include "CombineNode.h"
//#include "WriteFileNode.h"
//#include "GrayscaleNode.h"

Core::Core(QObject *parent) : QObject(parent) {
    QDir pluginDir = QDir::currentPath();
    pluginDir.cd("./plugins");

    QFileInfoList fileList = pluginDir.entryInfoList(QDir::Files);
    for (int i = 0; i < fileList.size(); i++) {
        qDebug() << fileList.at(i).absoluteFilePath();
        QPluginLoader loader(fileList.at(i).absoluteFilePath());
        QObject *plugin = loader.instance();

        if (loader.isLoaded()) {
            CvvINodeFactory *nodeFactory = qobject_cast<CvvINodeFactory*>(plugin);
            m_nodeFactory.append(nodeFactory);
            qDebug() << nodeFactory->getName();
        }
    }
}

Core::~Core() {

}

CvvINode *Core::createNode(QString nodeName) {
    for (int i = 0; i < m_nodeFactory.size(); i++) {
        qDebug() << m_nodeFactory.at(i)->getName() << " d" << nodeName;
        if (m_nodeFactory.at(i)->getName() == nodeName) {
            CvvINode *node = m_nodeFactory.at(i)->createNode();
            NodeControl *nodeControl = new NodeControl(node);
            m_nodeControl.append(nodeControl);

            if (nodeName == "Viewport") {
                makeGlobal(nodeControl);
            }

            return node;
        }
    }

    return nullptr;
}

void Core::displaySettings(CvvINode *node) {
    qDebug() << "Display";
    if (node) {
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
//        node->display(m_displayLayout);
    }
}

NodeControl *Core::getController(CvvINode *node) const {
    for (int i = 0; m_nodeControl.size(); i++) {
        if (m_nodeControl.at(i)->getNode() == node) {
            return m_nodeControl.at(i);
        }
    }

    return nullptr;
}

void Core::makeGlobal(NodeControl *nodeControl) {
    for (int i = 0; i < m_nodeControl.size(); i++) {
        if (m_nodeControl.at(i) != nodeControl) {
            m_nodeControl.at(i)->makeGlobal(false);
            m_nodeControl.at(i)->disconnect();
        } else {
            m_nodeControl.at(i)->makeGlobal(true);
            connect(m_nodeControl.at(i), SIGNAL(sendLocalTime(int)), this, SLOT(setGlobalTime(int)));
        }
    }
}

void Core::setGlobalTime(int globalTime) {
    qDebug() << globalTime;
    m_globalTime = globalTime;
    for (int i = 0; i < m_nodeControl.size(); i++) {
        if (!m_nodeControl.at(i)->isGlobal()) {
            m_nodeControl.at(i)->setGlobalTime(globalTime);
        }
    }
}
