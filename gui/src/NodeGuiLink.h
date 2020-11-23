#ifndef NODE_GUI_LINK_H
#define NODE_GUI_LINK_H

#include <QObject>
#include <cmath>

#include <QGraphicsLineItem>
#include <QPainter>
#include <QPointF>
#include <QTimer>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QPolygonF>

#include "NodeGuiPort.h"

class NodeGui;

class NodeGuiLink : public QObject, public QGraphicsLineItem {
    Q_OBJECT
public:
    NodeGuiLink(NodeGuiPort *outPort = nullptr, QObject *parent = nullptr);
    ~NodeGuiLink();

    void setDstPort(NodeGuiPort*);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    bool isValid();
    bool validate(NodeGuiPort*);
    bool isSelected();
    bool isConnected(NodeGui*);
    bool isActive();
    void unselect();

private:
    void mousePressEvent(QGraphicsSceneMouseEvent*);

private slots:
    void updatePaint();

private:
    QTimer *m_timer;
    NodeGuiPort *m_srcPort = nullptr;
    NodeGuiPort *m_dstPort = nullptr;
    QPointF m_startPoint;
    QPointF m_endPoint;
    QPolygonF m_selectionPolygon;
    qreal m_selectionOffset = 4;
    bool m_isSelected = false;
    bool m_active = false;
};

#endif // NODE_GUI_LINK_H
