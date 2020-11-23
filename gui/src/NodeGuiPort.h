#ifndef NODE_GUI_PORT_H
#define NODE_GUI_PORT_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QString>
#include <QGraphicsSceneMouseEvent>
#include <QVector>


class CvvINode;
class CvvINodePort;
class NodeGuiLink;

class NodeGuiPort : public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    NodeGuiPort(CvvINodePort *port = nullptr, QObject *parent = nullptr);
    ~NodeGuiPort();

    CvvINode *getParentNode() const;
    CvvINodePort *getPort() const;
    QString getName() const;
    int getDataType() const;
    bool isTaken() const;
    bool isActive() const;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
//    void linkInc();
//    void linkDec();
    void addLink(NodeGuiLink*);
    void removeLink(NodeGuiLink*);
    bool isSelected();
//    void unselect();
    void select(bool);
    void activate(bool);

    void updateConnection(NodeGuiPort*, bool);

private:
    CvvINodePort *m_port;
    QVector<NodeGuiLink*> m_link;
    bool m_isSelected = false;
};

#endif // NODE_GUI_PORT_H
