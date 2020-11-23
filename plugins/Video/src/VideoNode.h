#ifndef VIDEO_NODE_H
#define VIDEO_NODE_H

#include <QObject>
#include <QVBoxLayout>

#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>

#include "CvvINode.h"

class VideoNode;
class VideoSettings;
class RangeSlider;

namespace Ui {
class VideoSettings;
}

class VideoNodeFactory : public CvvINodeFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "VideoNodeFactory")
    Q_INTERFACES(CvvINodeFactory)
public:
    VideoNodeFactory(QObject *parent = nullptr);
    ~VideoNodeFactory();

    QString getName() const;
    QString getInfo() const;
    CvvINode *createNode();

private:
    QString m_name;
    QString m_info;
    QVector<CvvINode*> m_node;
};

class VideoNode : public CvvINode {
    Q_OBJECT
public:
    VideoNode(QObject *parent = nullptr);
    ~VideoNode();

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
    Ui::VideoSettings *m_ui;
    RangeSlider *m_rangeSlider;
    QVector<CvvINodePort*> m_dst;
    QVector<CvvINodePort*> m_src;
    QString m_name;
    VideoSettings *m_videoSettings = nullptr;
    QString m_path;
    cv::VideoCapture m_video;
    cv::Mat m_frame;
    cv::Mat m_startFrame;
    cv::Mat m_endFrame;
    int m_duration = 0;
    int m_timeRate = 1;
    int m_startFramePos = 0;
    int m_endFramePos = 0;
    int m_it = 0;
};

#endif // VIDEO_NODE_H
