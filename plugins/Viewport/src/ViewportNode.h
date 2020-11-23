#ifndef VIEWPORTNODE_H
#define VIEWPORTNODE_H

#include <QObject>

#include <opencv2/core.hpp>

#include "CvvINode.h"

class ViewportNode;
class ViewportDisplay;

namespace Ui {
class ViewportDisplay;
}

class ViewportNodeFactory : public CvvINodeFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ViewportNodeFactory")
    Q_INTERFACES(CvvINodeFactory)
public:
    ViewportNodeFactory(QObject *parent = nullptr);
    ~ViewportNodeFactory();

    QString getName() const;
    QString getInfo() const;
    CvvINode *createNode();

private:
    QString m_name;
    QString m_info;
    QVector<CvvINode*> m_node;
    cv::Mat m_frame;
};

class ViewportNode : public CvvINode {
    Q_OBJECT
public:
    ViewportNode(QObject *parent = nullptr);
    ~ViewportNode();

    void init();
    void setItemName(QString);
    QString getItemName() const;
    QVector<CvvINodePort*> getDst() const;
    QVector<CvvINodePort*> getSrc() const;
    void display(QVBoxLayout*) const;
    void displaySettings(QVBoxLayout*) const;

public slots:
    void updateNode();
    void windowResize();

private slots:
    void pause();
    void start();
    void stop();

private:
    QPixmap pixmapFromFrame(cv::Mat&, int, int);

signals:
    void setUpdateRate(int);
    void setDuration(int);
    void setTime(int);
    void pauseSignal();
    void startSignal();
    void stopSignal();

private:
    Ui::ViewportDisplay *m_ui;
    QVector<CvvINodePort*> m_dst;
    QVector<CvvINodePort*> m_src;
    QString m_name;
    int m_duration = 0;
    int m_timeRate = 1;
    ViewportDisplay *m_viewportDisplay;
    cv::Mat m_frame;
    int m_channels;
};

#endif // VIEWPORTNODE_H
