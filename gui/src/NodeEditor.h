#ifndef NODEEDITOR_H
#define NODEEDITOR_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QVector>
#include <QKeyEvent>
#include <QMouseEvent>

#include "ui_NodeEditor.h"
//#include "NodeManager.h"
#include "Core.h"

namespace Ui {
class NodeEditor;
}

class GUIManager;
class NodeGui;
class NodeGuiPort;
class NodeGuiLink;

class NodeEditor : public QMainWindow {
    Q_OBJECT
public:
    NodeEditor(QWidget *parent = nullptr);
    ~NodeEditor();

    void setCore(Core*);

public slots:
    void setSrcLink(NodeGuiPort *outPort);
    void setDstLink(NodeGuiPort *outPort);
private:
    void createNode(QString);

    void mousePressEvent(QMouseEvent*);
    void keyPressEvent(QKeyEvent*);

private slots:
    void createVideoNode();
    void createViewportNode();
    void zoomIn();
    void zoomOut();
private:
    Ui::NodeEditor *ui;
    GUIManager *m_gui;
    Core *m_core = nullptr;
    QGraphicsScene *m_scene;
    QVector<NodeGui*> m_node;
    QVector<NodeGuiLink*> m_link;
};

#endif // NODEEDITOR_H
