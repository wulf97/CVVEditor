#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QObject>

class GUIManager : public QObject {
    Q_OBJECT
public:
    GUIManager(QObject *parent = nullptr);

    void setCore(QObject*);
signals:
    void uploadVideo(QString*);
    void playVideo();
    void stopVideo();
    void pauseVideo();
    void videoLen(int);
    void updateFrame(QImage*);
    void stoped();
private:
    QObject *m_core;
};

#endif // GUIMANAGER_H
