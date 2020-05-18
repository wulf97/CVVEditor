#ifndef NODE_GUI_H
#define NODE_GUI_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QMoveEvent>
#include <QCursor>
#include <QVector>
#include <QTimer>

//#include "NodeManager.h"


class Core;
class CvvINode;
class NodeGuiPort;
class NodeGuiLink;

class NodeGui : public QObject, public QGraphicsItemGroup {
    Q_OBJECT
public:
    NodeGui(QString nodeName, Core *core, QObject *parent = nullptr);
    ~NodeGui();

    CvvINode *getNode() const;
    int isSelected() const;
    void unselect();
    void addLink(NodeGuiLink*);
    void removeLink(NodeGuiLink*);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    void setSrcLink(NodeGuiPort*);
    void setDstLink(NodeGuiPort*);

private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

private:
     Core *m_core = nullptr;
     CvvINode *m_node = nullptr;
     QVector<NodeGuiPort*> m_dstPort;
     QVector<NodeGuiPort*> m_srcPort;
     QVector<NodeGuiLink*> m_link;
     bool m_isSelected = false;
     int m_width = 180;
     int m_height = 70;
     int m_topHeadHeight = 50;
     int m_x;
     int m_y;
};

#endif // NODE_GUI_H
