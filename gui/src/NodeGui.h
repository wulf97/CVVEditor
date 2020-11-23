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
class GUIManager;
class CvvINode;
class NodeGuiPort;
class NodeGuiLink;

class NodeGui : public QObject, public QGraphicsItemGroup {
    Q_OBJECT
public:
    NodeGui(QString nodeName, Core *core, GUIManager *gui, QObject *parent = nullptr);
    ~NodeGui();

    CvvINode *getNode() const;
    int isSelected() const;
    void unselect();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    void setSrcLink(NodeGuiPort*);
    void setDstLink(NodeGuiPort*);

private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

private slots:
    void updatePaint();
private:
    QTimer *m_timer;
    Core *m_core = nullptr;
    GUIManager *m_gui = nullptr;
    CvvINode *m_node = nullptr;
    QVector<NodeGuiPort*> m_dstPort;
    QVector<NodeGuiPort*> m_srcPort;
    bool m_isSelected = false;
    int m_width = 180;
    int m_height = 70;
    int m_topHeadHeight = 50;
    int m_x;
    int m_y;
};

#endif // NODE_GUI_H
