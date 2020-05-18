#include "NodeGui.h"
#include "Core.h"
#include "CvvINode.h"
#include "CvvINodePort.h"
#include "NodeGuiPort.h"
#include "NodeGuiLink.h"

NodeGui::NodeGui(QString nodeName, Core *core, QObject *parent) : QObject(parent) {
    m_core = core;

    if (m_core) {
        m_node = m_core->createNode(nodeName);
        if (m_node) {
            QVector<CvvINodePort*> dst = m_node->getDst();
            QVector<CvvINodePort*> src = m_node->getSrc();

            m_height = m_topHeadHeight + 20*((dst.size() > src.size())? dst.size() : src.size());

            for (int i = 0; i < dst.size(); i++) {
                NodeGuiPort *port = new NodeGuiPort(dst.at(i), this);
                m_dstPort.append(port);
                port->setPos(3, m_topHeadHeight - 20 + 20*(i + 1));
                addToGroup(port);
            }

            for (int i = 0; i < src.size(); i++) {
                NodeGuiPort *port = new NodeGuiPort(src.at(i), this);
                m_srcPort.append(port);
                port->setPos(m_width - 14, m_topHeadHeight - 20 + 20*(i + 1));
                addToGroup(port);
            }
        }
    }
}

NodeGui::~NodeGui() {

}

CvvINode *NodeGui::getNode() const {
    return m_node;
}

int NodeGui::isSelected() const {
    return m_isSelected;
}

void NodeGui::unselect() {
    m_isSelected = false;
    update();
}

void NodeGui::addLink(NodeGuiLink *link) {
    m_link.append(link);
}

void NodeGui::removeLink(NodeGuiLink *link) {

}

QRectF NodeGui::boundingRect() const {
    return QRectF(0, 0, m_width, m_height);
}

void NodeGui::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(QColor("#c4ecee"));
    if (!m_isSelected) {
        painter->setBrush(QColor("#32414b"));
    } else {
        painter->setBrush(QColor("#5c778a"));
    }

    painter->drawRect(0, 0, m_width, m_height);
    painter->setBrush(QColor("#94a9b8"));
    painter->drawRect(0, 0, m_width, m_topHeadHeight - 10);
    painter->drawText(QRectF(0, 10, m_width, 20), Qt::AlignCenter, m_node->getItemName());

    for (int i = 0; i < m_dstPort.size(); i++) {
        painter->drawText(QRectF(0, m_topHeadHeight - 25 + 20*(i + 1), m_width/2, 20), Qt::AlignCenter, m_dstPort.at(i)->getName());
    }

    for (int i = 0; i < m_srcPort.size(); i++) {
        painter->drawText(QRectF(m_width/2, m_topHeadHeight - 25 + 20*(i + 1), m_width/2, 20), Qt::AlignCenter, m_srcPort.at(i)->getName());
    }

}

void NodeGui::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    setPos(mapToScene(event->pos()) - QPointF(m_x, m_y));
    setCursor(QCursor(Qt::ClosedHandCursor));

//    for (int i = 0; i < m_link.size(); i++) {
//        m_link.at(i)->update();
//    }
}

void NodeGui::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (boundingRect().contains(event->pos())) {
        m_isSelected = true;
        m_x = event->pos().x();
        m_y = event->pos().y();
    }

    for (int i = 0; i < m_dstPort.size(); i++) {
        if (m_dstPort.at(i)->boundingRect().contains(mapToItem(m_dstPort.at(i), event->pos()))) {
            m_isSelected = false;
            emit setDstLink(m_dstPort.at(i));
        }
    }

    for (int i = 0; i < m_srcPort.size(); i++) {
        if (m_srcPort.at(i)->boundingRect().contains(mapToItem(m_srcPort.at(i), event->pos()))) {
            m_isSelected = false;
            emit setSrcLink(m_srcPort.at(i));
        }
    }

    update();
}

void NodeGui::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    setCursor(QCursor(Qt::ArrowCursor));
}
