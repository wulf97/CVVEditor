#include "NodeGuiLink.h"
#include "NodeGui.h"

NodeGuiLink::NodeGuiLink(NodeGuiPort *srcPort, QObject *parent) : QObject(parent) {
    m_timer = new QTimer(this);
    m_srcPort = srcPort;

    if (m_srcPort) {
        m_srcPort->select(true);
    }

    connect(m_timer, SIGNAL(timeout()), this, SLOT(updatePaint()));

    m_timer->start(300);
}

NodeGuiLink::~NodeGuiLink() {
    if (m_srcPort && !m_dstPort) {
        m_srcPort->select(false);
    }

    if (m_dstPort) {
        m_srcPort->removeLink(this);
        m_dstPort->removeLink(this);
        m_dstPort->updateConnection(m_srcPort, false);
    }
}

void NodeGuiLink::setDstPort(NodeGuiPort *dstPort) {
    m_dstPort = dstPort;

    m_srcPort->addLink(this);
    m_dstPort->addLink(this);
    m_dstPort->updateConnection(m_srcPort, true);
    m_srcPort->select(false);

    if (m_srcPort && m_dstPort) {
        m_startPoint = m_srcPort->pos() + m_srcPort->group()->pos() + QPointF(6, 6);
        m_endPoint = m_dstPort->pos() + m_dstPort->group()->pos() + QPointF(6, 6);
        setLine(QLineF(QPointF(0, 0), m_endPoint - m_startPoint));

        QPolygonF nPolygon;
            qreal radAngle = line().angle()* M_PI / 180;
            qreal dx = m_selectionOffset * sin(radAngle);
            qreal dy = m_selectionOffset * cos(radAngle);
            QPointF offset1 = QPointF(dx, dy);
            QPointF offset2 = QPointF(-dx, -dy);
            nPolygon << line().p1() + offset1
                     << line().p1() + offset2
                     << line().p2() + offset2
                     << line().p2() + offset1;
            m_selectionPolygon = nPolygon;
    }

    setPos(m_startPoint);

    update();
}

QRectF NodeGuiLink::boundingRect() const {
    return m_selectionPolygon.boundingRect();
}

void NodeGuiLink::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QColor linkColor;

    if (m_dstPort->isActive()) {
        m_active = true;
        linkColor = QColor("#ff8533");
    } else {
        m_active = false;
        linkColor = QColor("#cccccc");
    }
    m_srcPort->activate(m_active);

    if (!m_isSelected)
        painter->setPen(QPen(linkColor, 3));
    else
        painter->setPen(QPen(linkColor, 6));

    if (m_srcPort && m_dstPort) {
        m_startPoint = m_srcPort->pos() + m_srcPort->group()->pos() + QPointF(6, 6);
        m_endPoint = m_dstPort->pos() + m_dstPort->group()->pos() + QPointF(6, 6);
        setLine(QLineF(QPointF(0, 0), m_endPoint - m_startPoint));
        painter->drawLine(line());

        QPolygonF nPolygon;
            qreal radAngle = line().angle()* M_PI / 180;
            qreal dx = m_selectionOffset * sin(radAngle);
            qreal dy = m_selectionOffset * cos(radAngle);
            QPointF offset1 = QPointF(dx, dy);
            QPointF offset2 = QPointF(-dx, -dy);
            nPolygon << line().p1() + offset1
                     << line().p1() + offset2
                     << line().p2() + offset2
                     << line().p2() + offset1;
            m_selectionPolygon = nPolygon;
    }

    setPos(m_startPoint);
}

bool NodeGuiLink::isValid() {
    if (m_srcPort && m_dstPort) return true;
    return false;
}

bool NodeGuiLink::validate(NodeGuiPort *dstPort) {
    if (dstPort) {
        // Если тип данных выхода совпадает с одним из типов на входе
        if ((m_srcPort->getDataType() & dstPort->getDataType()) != 0 && !(dstPort->isTaken())) {
            if (m_srcPort->getParentNode() != dstPort->getParentNode()) return true;
        }
    }

    return false;
}

bool NodeGuiLink::isSelected() {
    return m_isSelected;
}

bool NodeGuiLink::isConnected(NodeGui *node) {
    if (dynamic_cast<NodeGui*>(m_srcPort->parent()) == node) return true;
    if (dynamic_cast<NodeGui*>(m_dstPort->parent()) == node) return true;
    return false;
}

bool NodeGuiLink::isActive() {
    return m_active;
}

void NodeGuiLink::unselect() {
    m_isSelected = false;
    update();
}

void NodeGuiLink::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (m_selectionPolygon.containsPoint(event->pos(), Qt::WindingFill)) {
        m_isSelected = true;
        update();
    }
}

void NodeGuiLink::updatePaint() {
    update();
}
