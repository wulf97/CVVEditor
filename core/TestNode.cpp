#include "TestNode.h"
#include "CvvINode.h"
#include "CvvINodePort.h"

TestNodeFactory::TestNodeFactory(QObject *parent) {
    m_name = "Test";
}

TestNodeFactory::~TestNodeFactory() {

}

QString TestNodeFactory::getName() const {
    return m_name;
}

QString TestNodeFactory::getInfo() const {
    return m_info;
}

CvvINode *TestNodeFactory::createNode() {
    CvvINode *node = new TestNode(this);
    node->setItemName(m_name + "-" + QString::number(m_node.size()));
    m_node.append(node);

    return node;
}


/****************************/
TestNode::TestNode(QObject *parent) {
    CvvINodePort *dst_1 = new CvvINodePort(this, PORT_CONFIG_DST, "dst_1");
    CvvINodePort *dst_2 = new CvvINodePort(this, PORT_CONFIG_DST, "dst_2");
    CvvINodePort *src_1 = new CvvINodePort(this, PORT_CONFIG_SRC, "src_1");
    CvvINodePort *src_2 = new CvvINodePort(this, PORT_CONFIG_SRC, "src_2");

    dst_1->setDataType(CVV_32I | CVV_32F);
    dst_2->setDataType(CVV_32F);
    src_1->setDataType(CVV_32I);
    src_2->setDataType(CVV_32F);

    dst_1->printMetaData();
    dst_2->printMetaData();
    src_1->printMetaData();

    m_dst.append(dst_1);
    m_dst.append(dst_2);
    m_src.append(src_1);
    m_src.append(src_2);
}

TestNode::~TestNode() {

}

void TestNode::setItemName(QString name) {
    m_name = name;
}

QString TestNode::getItemName() const {
    return m_name;
}

QVector<CvvINodePort*> TestNode::getDst() const {
    return m_dst;
}

QVector<CvvINodePort*> TestNode::getSrc() const {
    return m_src;
}

void TestNode::updateNode() {
    qDebug() << m_name << "update";
}
