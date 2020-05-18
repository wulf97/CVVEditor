#include "NodeGuiPort.h"
#include "CvvINode.h"
#include "CvvINodePort.h"

NodeGuiPort::NodeGuiPort(CvvINodePort *port, QObject *parent) : QObject(parent) {
    m_port = port;
    QString toolTip;
    int dType = port->getDataType();

    if (dType) {
        if (CVV_8C & dType) {
            toolTip += "8C/";
        }

        if (CVV_32I & dType) {
            toolTip += "32I/";
        }

        if (CVV_32F & dType) {
            toolTip += "32F/";
        }

        if (CVV_VEC8C & dType) {
            toolTip += "VEC8C/";
        }

        if (CVV_VEC32I & dType) {
            toolTip += "VEC32I/";
        }

        if (CVV_VEC32F & dType) {
            toolTip += "VEC32F/";
        }

        toolTip.remove(toolTip.size() - 1, 1);
    }

    setToolTip(toolTip);
}

NodeGuiPort::~NodeGuiPort() {

}

CvvINode *NodeGuiPort::getParentNode() const {
    return m_port->getParentNode();
}

CvvINodePort *NodeGuiPort::getPort() const {
    return m_port;
}

QString NodeGuiPort::getName() const {
    return m_port->getName();
}

int NodeGuiPort::getDataType() const {
    return m_port->getDataType();
}

bool NodeGuiPort::isTaken() const {
    return m_isTaken;
}

QRectF NodeGuiPort::boundingRect() const {
    return QRectF(0, 0, 10, 10);
}

void NodeGuiPort::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(QPen(QColor("#ff8533"), 3));
    if (m_linkIncrement > 0 || m_isTaken) {
        painter->setBrush(QColor("#ff8533"));
    }

    painter->drawEllipse(0, 0, 12, 12);
}

void NodeGuiPort::linkInc() {
    if (!m_isSelected) {
        m_linkIncrement++;
        m_isSelected = true;
    }
}

void NodeGuiPort::linkDec() {
    if (m_linkIncrement > 0) {
        m_linkIncrement--;
        m_isSelected = false;
    }
}

bool NodeGuiPort::isSelected() {
    return m_isSelected;
}

void NodeGuiPort::unselect() {
    m_isSelected = false;
}

void NodeGuiPort::updateConnection(NodeGuiPort *port, bool fl) {
    CvvINodePort *srcPort = port->getPort();
    m_port->updateConnection(srcPort, fl);
    m_isTaken = fl;
}
