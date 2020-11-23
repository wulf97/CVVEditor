#include <math.h>
#include <QTime>

#include "GammaCorrectionNode.h"
#include "CvvINode.h"
#include "CvvINodePort.h"
#include "GammaCorrectionSettings.h"

GammaCorrectionNodeFactory::GammaCorrectionNodeFactory(QObject *parent) {
    m_name = "GammaCorrection";
    m_info = "Info";
}

GammaCorrectionNodeFactory::~GammaCorrectionNodeFactory() {

}

QString GammaCorrectionNodeFactory::getName() const {
    return m_name;
}

QString GammaCorrectionNodeFactory::getInfo() const {
    return m_info;
}

CvvINode *GammaCorrectionNodeFactory::createNode() {
    CvvINode *node = new GammaCorrectionNode(this);
    node->setItemName(m_name + "-" + QString::number(m_node.size()));
    m_node.append(node);

    return node;
}

GammaCorrectionNode::GammaCorrectionNode(QObject *parent) {
    m_gammaCorrectionSettings = new GammaCorrectionSettings();

    CvvINodePort *dst_1 = new CvvINodePort(this, PORT_CONFIG_DST, "in");
    CvvINodePort *src_1 = new CvvINodePort(this, PORT_CONFIG_SRC, "out");

    dst_1->setDataType(CVV_IMG8C1 | CVV_IMG8C3);
    src_1->setDataType(CVV_IMG8C3);

    dst_1->activate(true);

    m_dst.append(dst_1);
    m_src.append(src_1);
}

GammaCorrectionNode::~GammaCorrectionNode() {
    delete m_gammaCorrectionSettings;
}

void GammaCorrectionNode::init() {
//    qDebug() << "init()" << m_dst.at(0)->getDuration();
    emit setUpdateRate(23);
    emit setDuration(m_dst.at(0)->getDuration());
}

void GammaCorrectionNode::setItemName(QString name) {
    m_name = name;
}

QString GammaCorrectionNode::getItemName() const {
    return m_name;
}

QVector<CvvINodePort*> GammaCorrectionNode::getDst() const {
    return m_dst;
}

QVector<CvvINodePort*> GammaCorrectionNode::getSrc() const {
    return m_src;
}

void GammaCorrectionNode::display(QVBoxLayout*) const {

}

void GammaCorrectionNode::displaySettings(QVBoxLayout *layout) const {
    if (layout) {
        layout->addWidget(m_gammaCorrectionSettings);
    }
}

void GammaCorrectionNode::updateNode() {
    cv::Mat frame;
    cv::Mat gray;
    cv::Mat buf;
    m_dst.at(0)->getData(CVV_IMG8C3, frame);
    double gamma = 0.2;
    uchar col[256];
    for (int i = 0; i < sizeof(col); i++) {
        col[i] = std::pow((double)(i/255.0), gamma)*255;
//        qDebug() <<"gsgdzfgsshf " << i << " " <<(int)col[i];
    }
    if (!frame.empty()) {
        gray = frame.clone();
        for (int i = 0; i < gray.rows; i++) {
            for (int j = 0; j < gray.cols; j++) {
                for (int k = 0; k < gray.channels(); k++) {
                    uchar val = gray.at<cv::Vec3b>(i, j)[k];
                    gray.at<cv::Vec3b>(i, j)[k] = col[val];
                }
            }
        }

        cv::cvtColor(gray, buf, cv::COLOR_BGR2RGB);
        m_src.at(0)->setData(buf);
    }

    emit setTime(m_dst.at(0)->getTime());
}
