#include "NodeControl.h"
#include "CvvINode.h"
#include "CvvINodePort.h"

NodeControl::NodeControl(CvvINode *node, QObject *parent) : QObject(parent) {
    m_timer = new QTimer(this);
    m_node = node;

    if (m_node->getSrc().size() > 0) {
        for (int i = 0; i < m_node->getDst().size(); i++) {
            m_node->getDst().at(i)->turnOn(false);
        }
    }

    connect(node, SIGNAL(setUpdateRate(int)), this, SLOT(setUpdateRate(int)));
    connect(node, SIGNAL(setDuration(int)), this, SLOT(setDuration(int)));
    connect(node, SIGNAL(setTime(int)), this, SLOT(setLocalTime(int)));
    connect(node, SIGNAL(pauseSignal()), this, SLOT(pause()));
    connect(node, SIGNAL(startSignal()), this, SLOT(start()));
    connect(node, SIGNAL(stopSignal()), this, SLOT(stop()));

    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateNode()));

    node->init();
}

NodeControl::~NodeControl() {
    delete m_timer;
    delete m_node;
}

CvvINode *NodeControl::getNode() const {
    return m_node;
}

int NodeControl::getDuration() const {
    return m_duration;
}

void NodeControl::makeGlobal(bool fl) {
    m_isGlobal = fl;
}

bool NodeControl::isGlobal() {
    return m_isGlobal;
}

void NodeControl::setLocalTime(int localTime) {
    m_localTime = localTime;

    for (int i = 0; i < m_node->getSrc().size(); i++) {
        m_node->getSrc().at(i)->setTime(localTime);
    }
}

void NodeControl::setGlobalTime(int globalTime) {
    m_globalTime = globalTime;
}

void NodeControl::updateNode() {
    bool fl = false;
    m_localTime = (double)m_it/m_rate*1000;

    if (m_isStart) {
        if (!m_isGlobal) {
            if (m_localTime < m_duration) {
                for (int i = 0; i < m_node->getSrc().size(); i++) {
                    if (m_node->getSrc().at(i)->isActive()) {
                        for (int j = 0; j < m_node->getDst().size(); j++) {
                            m_node->getDst().at(j)->turnOn(true);
                        }
                        fl = true;
                        m_it++;
                        m_node->updateNode();
                        break;
                    }
                }

                if (!fl && m_node->getSrc().size() > 0) {
                    for (int j = 0; j < m_node->getDst().size(); j++) {
                        m_node->getDst().at(j)->turnOn(false);
                    }
                }
            } else {
                if (m_globalTime == 0) {
                    m_it = 0;
                    m_localTime = 0;
                    m_node->init();
                }
//                m_localTime = 0;
//                m_it = 0;
            }
        } else {
            qDebug() << "DUR " << m_duration << "(" << m_localTime << ")";
            if (m_localTime < m_duration) {
                m_node->updateNode();
                m_it++;

                emit sendLocalTime(m_localTime);
            } else {
                m_it = 0;
                m_localTime = 0;

                emit sendLocalTime(m_localTime);
            }
        }
    }
}

void NodeControl::setUpdateRate(int rate) {
    m_rate = rate;
    if (m_rate) {
        m_timer->start(1000/rate);
    }
}

void NodeControl::setDuration(int duration) {
    m_duration = duration;

    for (int i = 0; i < m_node->getSrc().size(); i++) {
        m_node->getSrc().at(i)->setDuration(duration);
    }
}

void NodeControl::pause() {
    m_isStart = false;
    qDebug() << "pause";
}

void NodeControl::start() {
    m_isStart = true;
}

void NodeControl::stop() {
    m_isStart = false;
}
