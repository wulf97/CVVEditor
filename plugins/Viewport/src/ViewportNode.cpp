#include <QTime>

#include "ViewportNode.h"
#include "CvvINode.h"
#include "CvvINodePort.h"
#include "ViewportDisplay.h"

ViewportNodeFactory::ViewportNodeFactory(QObject *parent) {
    m_name = "Viewport";
    m_info = "Info";
}

ViewportNodeFactory::~ViewportNodeFactory() {

}

QString ViewportNodeFactory::getName() const {
    return m_name;
}

QString ViewportNodeFactory::getInfo() const {
    return m_info;
}

CvvINode *ViewportNodeFactory::createNode() {
    CvvINode *node = new ViewportNode(this);
    node->setItemName(m_name + "-" + QString::number(m_node.size()));
    m_node.append(node);

    return node;
}

ViewportNode::ViewportNode(QObject *parent) {
    m_viewportDisplay = new ViewportDisplay();
    m_ui = m_viewportDisplay->getUi();

    CvvINodePort *dst_1 = new CvvINodePort(this, PORT_CONFIG_DST, "in");

    dst_1->setDataType(CVV_IMG8C1 | CVV_IMG8C2 | CVV_IMG8C3);

    dst_1->activate(true);

    m_dst.append(dst_1);

    connect(m_viewportDisplay, SIGNAL(windowResize()), this, SLOT(windowResize()));
    connect(m_ui->pause, SIGNAL(released()), this, SLOT(pause()));
    connect(m_ui->start, SIGNAL(released()), this, SLOT(start()));
}

ViewportNode::~ViewportNode() {

}

void ViewportNode::init() {

//    m_ui->startTime->setText(QTime::fromMSecsSinceStartOfDay(m_dst.at(0)->getTime()).toString("hh:mm:ss"));
//    m_ui->endTime->setText(QTime::fromMSecsSinceStartOfDay(m_duration).toString("hh:mm:ss"));

    emit setUpdateRate(23);
    emit setDuration(m_dst.at(0)->getDuration());
}

void ViewportNode::setItemName(QString name) {
    m_name = name;
}

QString ViewportNode::getItemName() const {
    return m_name;
}

QVector<CvvINodePort*> ViewportNode::getDst() const {
    return m_dst;
}

QVector<CvvINodePort*> ViewportNode::getSrc() const {
    return m_src;
}

void ViewportNode::display(QVBoxLayout *layout) const {
    if (layout) {
        layout->addWidget(m_viewportDisplay);
    }

}

void ViewportNode::displaySettings(QVBoxLayout *layout) const {
    if (layout) {
        layout->addWidget(m_viewportDisplay);
    }
}

void ViewportNode::updateNode() {
    m_dst.at(0)->getData(CVV_IMG8C3, m_frame);

    m_channels = m_frame.channels();

    m_ui->startTime->setText(QTime::fromMSecsSinceStartOfDay(m_dst.at(0)->getTime()).toString("hh:mm:ss"));
    m_ui->endTime->setText(QTime::fromMSecsSinceStartOfDay(m_dst.at(0)->getDuration()).toString("hh:mm:ss"));
    m_ui->slider->setRange(0, m_dst.at(0)->getDuration());
    m_ui->slider->setValue(m_dst.at(0)->getTime());
    m_ui->viewport->setPixmap(pixmapFromFrame(m_frame, m_ui->viewport->width(), m_ui->viewport->height()));

    emit setTime(m_dst.at(0)->getTime());
}

void ViewportNode::windowResize() {
    if (!m_frame.empty()) {
        m_ui->viewport->setPixmap(pixmapFromFrame(m_frame, m_ui->viewport->width(), m_ui->viewport->height()));
    }
}

void ViewportNode::pause() {
    m_dst.at(0)->activate(false);
    emit pauseSignal();
}

void ViewportNode::start() {
    m_dst.at(0)->activate(true);
    emit startSignal();
}

void ViewportNode::stop() {
    emit stopSignal();

}

QPixmap ViewportNode::pixmapFromFrame(cv::Mat &frame, int w, int h) {
    QImage img;
    if (m_channels == 1) {
        img = QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_Grayscale8);
    } else if (m_channels == 3) {
        img = QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    }

    if ((float)w/h < (float)frame.cols/frame.rows) {
        img  = img.scaledToWidth(w);
    } else {
        img  = img.scaledToHeight(h);
    }

    return QPixmap::fromImage(img);
}
