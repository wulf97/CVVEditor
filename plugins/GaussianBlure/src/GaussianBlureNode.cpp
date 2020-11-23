#include <QTime>

#include "GaussianBlureNode.h"
#include "CvvINode.h"
#include "CvvINodePort.h"
#include "GaussianBlureSettings.h"

GaussianBlureNodeFactory::GaussianBlureNodeFactory(QObject *parent) {
    m_name = "GaussianBlure";
    m_info = "Info";
}

GaussianBlureNodeFactory::~GaussianBlureNodeFactory() {

}

QString GaussianBlureNodeFactory::getName() const {
    return m_name;
}

QString GaussianBlureNodeFactory::getInfo() const {
    return m_info;
}

CvvINode *GaussianBlureNodeFactory::createNode() {
    CvvINode *node = new GaussianBlureNode(this);
    node->setItemName(m_name + "-" + QString::number(m_node.size()));
    m_node.append(node);

    return node;
}

GaussianBlureNode::GaussianBlureNode(QObject *parent) {
    m_gaussianBlureSettings = new GaussianBlureSettings();

    CvvINodePort *dst_1 = new CvvINodePort(this, PORT_CONFIG_DST, "in");
    CvvINodePort *src_1 = new CvvINodePort(this, PORT_CONFIG_SRC, "out");

    dst_1->setDataType(CVV_IMG8C1 | CVV_IMG8C3);
    src_1->setDataType(CVV_IMG8C3);

    dst_1->activate(true);

    m_dst.append(dst_1);
    m_src.append(src_1);
}

GaussianBlureNode::~GaussianBlureNode() {
    delete m_gaussianBlureSettings;
}

void GaussianBlureNode::init() {
//    qDebug() << "init()" << m_dst.at(0)->getDuration();
    emit setUpdateRate(23);
    emit setDuration(m_dst.at(0)->getDuration());
}

void GaussianBlureNode::setItemName(QString name) {
    m_name = name;
}

QString GaussianBlureNode::getItemName() const {
    return m_name;
}

QVector<CvvINodePort*> GaussianBlureNode::getDst() const {
    return m_dst;
}

QVector<CvvINodePort*> GaussianBlureNode::getSrc() const {
    return m_src;
}

void GaussianBlureNode::display(QVBoxLayout*) const {

}

void GaussianBlureNode::displaySettings(QVBoxLayout *layout) const {
    if (layout) {
        layout->addWidget(m_gaussianBlureSettings);
    }
}

void GaussianBlureNode::updateNode() {
    cv::Mat frame;
    cv::Mat gray;
    cv::Mat buf;
    m_dst.at(0)->getData(CVV_IMG8C3, frame);
    if (!frame.empty()) {
        cv::GaussianBlur(frame, gray, cv::Size(m_gaussianBlureSettings->getBlurRadius(), m_gaussianBlureSettings->getBlurRadius()), m_gaussianBlureSettings->getSigma(), m_gaussianBlureSettings->getSigma());
        cv::cvtColor(gray, buf, cv::COLOR_BGR2RGB);


        m_src.at(0)->setData(buf);
    }

    emit setTime(m_dst.at(0)->getTime());
}
