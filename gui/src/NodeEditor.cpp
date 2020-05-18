#include <QAction>
#include <QDebug>

#include "GUIManager.h"
#include "CvvINode.h"
#include "CvvINodePort.h"
#include "NodeEditor.h"
#include "NodeGui.h"
#include "NodeGuiPort.h"
#include "NodeGuiLink.h"

static int randomBetween(int low, int high) {
    return (qrand() % ((high + 1) - low) + low);
}

NodeEditor::NodeEditor(QWidget *parent) :
                       QMainWindow(parent),
                       ui(new Ui::NodeEditor) {
    m_gui = dynamic_cast<GUIManager*>(parent);
    m_scene = new QGraphicsScene(this);

    ui->setupUi(this);

    connect(ui->actionVideo, &QAction::triggered, this, &NodeEditor::createVideoNode);
    connect(ui->actionViewport, &QAction::triggered, this, &NodeEditor::createViewportNode);
    connect(ui->actionZoomIn, &QAction::triggered, this, &NodeEditor::zoomIn);
    connect(ui->actionZoomOut, &QAction::triggered, this, &NodeEditor::zoomOut);

    ui->graphicsView->setScene(m_scene);
}

NodeEditor::~NodeEditor() {
    delete ui;
}

void NodeEditor::setCore(Core *core) {
    m_core = core;
}

void NodeEditor::setSrcLink(NodeGuiPort *srcPort) {
    if (srcPort) {
        if (!srcPort->isSelected()) {
            if (m_link.size() > 0) {
                if (m_link.last()->isValid()) {
                    qDebug() << "Src port";
                    NodeGuiLink *link = new NodeGuiLink(srcPort, this);
                    m_link.append(link);
                }
            } else {
                qDebug() << "Src port";
                NodeGuiLink *link = new NodeGuiLink(srcPort, this);
                m_link.append(link);
            }
        }
    }
}

void NodeEditor::setDstLink(NodeGuiPort *dstPort) {
    if (dstPort) {
        if (m_link.size() > 0) {
            if (!m_link.last()->isValid() && m_link.last()->validate(dstPort)) {
                qDebug() << "Dst port";
                m_link.last()->setDstPort(dstPort);
                dynamic_cast<NodeGui*>(dstPort->parent())->addLink(m_link.last());
                m_scene->addItem(m_link.last());
//                m_scene->update();
//                ui->graphicsView->update();
            }
        }
    }

    qDebug() << "**************";
    for (int i = 0; i < m_node.size(); i++) {
        qDebug() << "***";
            for (int j = 0; j < m_node.at(i)->getNode()->getDst().size(); j++) {
               m_node.at(i)->getNode()->getDst().at(j)->printMetaData();
            }

            for (int j = 0; j < m_node.at(i)->getNode()->getSrc().size(); j++) {
               m_node.at(i)->getNode()->getSrc().at(j)->printMetaData();
            }
    }
}

void NodeEditor::mousePressEvent(QMouseEvent *event) {
    for (int i = 0; i < m_node.size(); i++) {
        m_node.at(i)->unselect();
    }

    for (int i = 0; i < m_link.size(); i++) {
        m_link.at(i)->unselect();
    }

    if (m_link.size() > 0) {
        if (!m_link.last()->isValid()) {
            delete m_link.last();
            m_link.remove(m_link.size() - 1);
            qDebug() << "rem " << m_link.size();
        }
    }
}

void NodeEditor::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key::Key_Delete) {
        for (int i = 0; i < m_node.size(); i++) {
            if (m_node.at(i)->isSelected()) {
                m_scene->removeItem(m_node.at(i));
                for (int j = 0; j < m_link.size(); j++) {
                    if (m_link.at(j)->isConnected(m_node.at(i))) {
                        delete m_link.at(j);
                        m_link.remove(j);
                        j--;
                    }
                }
                delete m_node.at(i);
                m_node.remove(i);
                i--;
            }
        }

        for (int i = 0; i < m_link.size(); i++) {
            if (m_link.at(i)->isSelected()) {
                m_scene->removeItem(m_link.at(i));
                delete m_link.at(i);
                m_link.remove(i);
                i--;
            }
        }
    }
}

void NodeEditor::createNode(QString nodeName) {
    NodeGui *node = new NodeGui(nodeName, m_core, this);

    m_scene->addItem(node);
    node->setPos(randomBetween(0, 600), randomBetween(0, 300));

    connect(node, SIGNAL(setSrcLink(NodeGuiPort*)), this, SLOT(setSrcLink(NodeGuiPort*)));
    connect(node, SIGNAL(setDstLink(NodeGuiPort*)), this, SLOT(setDstLink(NodeGuiPort*)));

    m_node.append(node);
}

void NodeEditor::createVideoNode() {
    qDebug() << "video";
    createNode("Test");
}

void NodeEditor::createViewportNode() {
    qDebug() << "viewport";
    createNode("Viewport");
}

void NodeEditor::zoomIn() {
    ui->graphicsView->scale(2, 2);
}

void NodeEditor::zoomOut() {
    ui->graphicsView->scale(0.5, 0.5);
}
