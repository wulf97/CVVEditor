#include <QDebug>

#include "Core.h"

Core::Core(QObject *parent) : QObject(parent) {
    m_VLoader = new VideoLoader(this);
    m_VSeq = new VideoSeq(this);
}

void Core::testSignals() {
    qDebug() << "********** Test core **********" << endl;
}

VideoLoader *Core::getVideoLoader() {
    return m_VLoader;
}

VideoSeq *Core::getVideoSeq() {
    return m_VSeq;
}
