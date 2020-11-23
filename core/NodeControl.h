#ifndef NODE_CONTROL_H
#define NODE_CONTROL_H

#include <QObject>
#include <QTimer>

class CvvINode;

class NodeControl : public QObject {
    Q_OBJECT
public:
    NodeControl(CvvINode *node, QObject *parent = nullptr);
    ~NodeControl();

    CvvINode *getNode() const;
    int getDuration() const;
    void makeGlobal(bool);
    bool isGlobal();

public slots:
    void setLocalTime(int);
    void setGlobalTime(int);
    void updateNode();
    void setUpdateRate(int);
    void setDuration(int);
    void pause();
    void start();
    void stop();

signals:
    void sendLocalTime(int);

private:
    bool m_isGlobal = false;
    bool m_isStart = true;
    int m_it = 0;
    QTimer *m_timer;
    CvvINode *m_node = nullptr;
    int m_globalTime = 0;
    int m_localTime = 0;
    int m_rate = 0;
    int m_duration = 0;
    int m_timeOffset = 0;
};

#endif // NODE_CONTROL_H
