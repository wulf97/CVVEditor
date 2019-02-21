#ifndef CORE_H
#define CORE_H

#include <QObject>

#include "VideoLoader.h"

class Core : public QObject {
    Q_OBJECT
public:
    Core(QObject *parent = nullptr);

    void setGUI(QObject*);
signals:
    void uploadVideo(QString*);
    void playVideo();
    void stopVideo();
    void pauseVideo();
    void videoLen(int);
    void updateFrame(QImage*);
    void stoped();
private:
    QObject *m_gui;
    VideoLoader *m_VLoader = nullptr;
};

#endif // CORE_H
