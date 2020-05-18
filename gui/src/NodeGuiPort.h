#ifndef NODE_GUI_PORT_H
#define NODE_GUI_PORT_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QString>
#include <QGraphicsSceneMouseEvent>


class CvvINode;
class CvvINodePort;

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

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    void linkInc();
    void linkDec();
    bool isSelected();
    void unselect();

    void updateConnection(NodeGuiPort*, bool);

private:
    CvvINodePort *m_port;
    bool m_isSelected = false;
    bool m_isTaken = false;
    int m_linkIncrement = 0;
};

#endif // NODE_GUI_PORT_H
