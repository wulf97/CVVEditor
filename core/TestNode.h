#ifndef TESTNODE_H
#define TESTNODE_H

#include <QObject>
#include <QVector>

#include "CvvINode.h"

class TestNodeFactory : public CvvINodeFactory {
Q_OBJECT
public:
    TestNodeFactory(QObject *parent = nullptr);
    ~TestNodeFactory();

    QString getName() const;
    QString getInfo() const;
    CvvINode *createNode();

private:
    QString m_name;
    QString m_info;
    QVector<CvvINode*> m_node;
};

class TestNode : public CvvINode {
Q_OBJECT
public:
    TestNode(QObject *parent = nullptr);
    ~TestNode();

    void setItemName(QString);
    QString getItemName() const;
    QVector<CvvINodePort*> getDst() const;
    QVector<CvvINodePort*> getSrc() const;

public slots:
    void updateNode();
private:
    QVector<CvvINodePort*> m_dst;
    QVector<CvvINodePort*> m_src;
    QString m_name;
};

#endif // TESTNODE_H
