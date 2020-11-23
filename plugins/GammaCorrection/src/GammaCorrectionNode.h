#ifndef GAMMA_CORRECTION_NODE_H
#define GAMMA_CORRECTION_NODE_H

#include <QObject>
#include <QVBoxLayout>

#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>

#include "CvvINode.h"

class GammaCorrectionNode;
class GammaCorrectionSettings;

namespace Ui {
class GammaCorrectionSettings;
}

class GammaCorrectionNodeFactory : public CvvINodeFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "GammaCorrectionNodeFactory")
    Q_INTERFACES(CvvINodeFactory)
public:
    GammaCorrectionNodeFactory(QObject *parent = nullptr);
    ~GammaCorrectionNodeFactory();

    QString getName() const;
    QString getInfo() const;
    CvvINode *createNode();

private:
    QString m_name;
    QString m_info;
    QVector<CvvINode*> m_node;
};


class GammaCorrectionNode : public CvvINode {
    Q_OBJECT
public:
    GammaCorrectionNode(QObject *parent = nullptr);
    ~GammaCorrectionNode();

    void init();
    void setItemName(QString);
    QString getItemName() const;
    QVector<CvvINodePort*> getDst() const;
    QVector<CvvINodePort*> getSrc() const;
    void display(QVBoxLayout*) const;
    void displaySettings(QVBoxLayout*) const;

public slots:
    void updateNode();

private slots:
    void openVideo(QString);
    void chengeTimeRate(int);
    void setStartTime(int);
    void setEndTime(int);
    void windowResize();

signals:
    void setUpdateRate(int);
    void setDuration(int);
    void setTime(int);
    void pauseSignal();
    void startSignal();
    void stopSignal();

private:
    Ui::GammaCorrectionSettings *m_ui;
    QVector<CvvINodePort*> m_dst;
    QVector<CvvINodePort*> m_src;
    QString m_name;
    GammaCorrectionSettings *m_gammaCorrectionSettings;
};

#endif // GAMMA_CORRECTION_NODE_H
