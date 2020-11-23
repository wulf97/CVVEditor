#include <QTime>

#include "VideoNode.h"
#include "CvvINode.h"
#include "CvvINodePort.h"
#include "VideoSettings.h"
#include "RangeSlider.h"

VideoNodeFactory::VideoNodeFactory(QObject *parent) {
    m_name = "Video";
    m_info = "Info";
}

VideoNodeFactory::~VideoNodeFactory() {

}

QString VideoNodeFactory::getName() const {
    return m_name;
}

QString VideoNodeFactory::getInfo() const {
    return m_info;
}

CvvINode *VideoNodeFactory::createNode() {
    CvvINode *node = new VideoNode(this);
    node->setItemName(m_name + "-" + QString::number(m_node.size()));
    m_node.append(node);

    return node;
}

VideoNode::VideoNode(QObject *parent) {
    m_videoSettings = new VideoSettings();
    m_ui = m_videoSettings->getUi();
    m_rangeSlider = m_videoSettings->getRangeSlider();

    CvvINodePort *src_1 = new CvvINodePort(this, PORT_CONFIG_SRC, "out");

    src_1->setDataType(CVV_IMG8C3);

    m_src.append(src_1);

    connect(m_videoSettings, SIGNAL(openVideo(QString)), this, SLOT(openVideo(QString)));
    connect(m_videoSettings, SIGNAL(windowResize()), this, SLOT(windowResize()));

    connect(m_ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(chengeTimeRate(int)));
    connect(m_rangeSlider, SIGNAL(lowerValueChanged(int)), this, SLOT(setStartTime(int)));
    connect(m_rangeSlider, SIGNAL(upperValueChanged(int)), this, SLOT(setEndTime(int)));
}

VideoNode::~VideoNode() {
    delete m_videoSettings;
}

void VideoNode::init() {
    m_it = 0;
    m_duration = (m_endFramePos - m_startFramePos)/(double)m_timeRate*1000;

    m_ui->spinBox->setValue(m_timeRate);
    m_ui->startTime->setText(QTime::fromMSecsSinceStartOfDay(m_startFramePos/m_timeRate*1000).toString("hh:mm:ss"));
    m_ui->endTime->setText(QTime::fromMSecsSinceStartOfDay(m_endFramePos/m_timeRate*1000).toString("hh:mm:ss"));

    if (m_video.isOpened()) {
        m_video.set(cv::CAP_PROP_POS_FRAMES, m_startFramePos);
    }

    emit setUpdateRate(m_timeRate);
    emit setDuration(m_duration);
}

void VideoNode::setItemName(QString name) {
    m_name = name;
}

QString VideoNode::getItemName() const {
    return m_name;
}

QVector<CvvINodePort*> VideoNode::getDst() const {
    return m_dst;
}

QVector<CvvINodePort*> VideoNode::getSrc() const {
    return m_src;
}

void VideoNode::display(QVBoxLayout*) const {

}

void VideoNode::displaySettings(QVBoxLayout *layout) const {
    if (layout) {
        layout->addWidget(m_videoSettings);
    }
}

void VideoNode::updateNode() {
    if (m_video.isOpened()) {
        m_video >> m_frame;

        m_it++;

//        qDebug() << m_startFramePos;
//        qDebug() << "*" << m_video.get(cv::CAP_PROP_POS_FRAMES) << " " << m_it << " " << m_duration/1000.*m_timeRate;

//        qDebug() << m_frame.cols;
        emit m_src.at(0)->sendData((Timg)m_frame);

        emit setTime((double)m_it/m_timeRate*1000);

        if (!m_frame.empty()) {
            m_ui->currentFrame->setPixmap(pixmapFromFrame(m_frame, m_ui->currentFrame->width(), m_ui->currentFrame->height()));
        }
    }
}

void VideoNode::openVideo(QString path) {
    m_path = path;

    m_video.open(path.toStdString());

    if (m_video.isOpened()) {
        m_timeRate = m_video.get(cv::CAP_PROP_FPS);
        m_endFramePos = m_video.get(cv::CAP_PROP_FRAME_COUNT);
        m_duration = m_endFramePos/m_timeRate*1000;

        m_rangeSlider->setMaximum(m_endFramePos/m_timeRate*1000);

        chengeTimeRate(m_timeRate);
    }
}

void VideoNode::chengeTimeRate(int value) {
    m_timeRate = value;
    m_rangeSlider->setMaximum(m_video.get(cv::CAP_PROP_FRAME_COUNT) / m_timeRate * 1000);
    init();
}

void VideoNode::setStartTime(int startTime) {
    cv::Mat frame;
    m_startFramePos = startTime/1000.*m_timeRate;

    if (m_video.isOpened()) {
        m_video.set(cv::CAP_PROP_POS_FRAMES, m_startFramePos);

        m_video >> frame;

        if (!frame.empty()) {
            m_startFrame = frame;
            m_ui->startFrame->setPixmap(pixmapFromFrame(frame, m_ui->startFrame->width(), m_ui->startFrame->height()));
        }
        m_video.set(cv::CAP_PROP_POS_FRAMES, m_startFramePos);
        qDebug() << m_video.get(cv::CAP_PROP_POS_FRAMES);
    }

    init();
}

void VideoNode::setEndTime(int endTime) {
    cv::Mat frame;
    m_endFramePos = endTime/1000.*m_timeRate;

    if (m_video.isOpened()) {
        m_video.set(cv::CAP_PROP_POS_FRAMES, m_endFramePos);

        m_video >> frame;

        if (!frame.empty()) {
            m_endFrame = frame;
            m_ui->endFrame->setPixmap(pixmapFromFrame(frame, m_ui->endFrame->width(), m_ui->endFrame->height()));
        }
        m_video.set(cv::CAP_PROP_POS_FRAMES, m_startFramePos);
    }

    init();
}

void VideoNode::windowResize() {
    if (!m_startFrame.empty()) {
        m_ui->startFrame->setPixmap(pixmapFromFrame(m_startFrame, m_ui->startFrame->width(), m_ui->startFrame->height()));
    }

    if (!m_endFrame.empty()) {
        m_ui->endFrame->setPixmap(pixmapFromFrame(m_endFrame, m_ui->endFrame->width(), m_ui->endFrame->height()));
    }
}

QPixmap VideoNode::pixmapFromFrame(cv::Mat &frame, int w, int h) {
    QImage img = QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_BGR888);

    if ((float)w/h < (float)frame.cols/frame.rows) {
        img  = img.scaledToWidth(w);
    } else {
        img  = img.scaledToHeight(h);
    }

    return QPixmap::fromImage(img);
}
