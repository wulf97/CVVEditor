#include "NodeGuiPort.h"
#include "CvvINode.h"
#include "CvvINodePort.h"
#include "NodeGuiLink.h"

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
    if (m_link.size() > 0) return true;
    return false;
}

bool NodeGuiPort::isActive() const {
    return m_port->isActive();
}

QRectF NodeGuiPort::boundingRect() const {
    return QRectF(0, 0, 10, 10);
}

void NodeGuiPort::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QColor portColor;

    if (isActive()) {
        portColor = QColor("#ff8533");
    } else {
        portColor = QColor("#cccccc");
    }

    painter->setPen(QPen(portColor, 3));
    if (m_link.size() > 0 || isSelected()) {
        painter->setBrush(portColor);
    }

    painter->drawEllipse(0, 0, 12, 12);
}

void NodeGuiPort::addLink(NodeGuiLink *link) {
    m_link.append(link);
}

void NodeGuiPort::removeLink(NodeGuiLink *link) {
    for (int i = 0; i < m_link.size(); i++) {
        if (m_link.at(i) == link) {
            m_link.remove(i);
            i--;
            break;
        }
    }
}

bool NodeGuiPort::isSelected() {
    return m_isSelected;
}

void NodeGuiPort::select(bool isSelected) {
    m_isSelected = isSelected;

    update();
}

void NodeGuiPort::activate(bool isActive) {
    bool fl = false;

    if (m_port->getConfig() == PORT_CONFIG_SRC) {
        for (int i = 0; i < m_link.size(); i++) {
            if (m_link.at(i)->isActive()) {
                fl = true;
                break;
            }
        }

        m_port->activate(fl);
    }
}

void NodeGuiPort::updateConnection(NodeGuiPort *port, bool fl) {
    CvvINodePort *srcPort = port->getPort();
    m_port->updateConnection(srcPort, fl);
    if (fl) {
        if (m_port->isActive())
            port->activate(true);
    } else {
        if (m_port->isActive())
            port->activate(false);
    }
}
