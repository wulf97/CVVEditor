#include <QDebug>

#include "Core.h"
#include "IFilter.h"

Core::Core(QObject *parent) : QObject(parent) {
    m_VLoader = new VideoLoader(this);
    m_VSeq = new VideoSeq(this);

    PluginManager *pManager = new PluginManager(this);

    pManager->load();
    for (int i = 0; i < pManager->size(); i++) {
        qDebug() << "Filter: " << dynamic_cast<IFilter*>(pManager->get(i))->getName();
    }

}

VideoLoader *Core::getVideoLoader() {
    return m_VLoader;
}

VideoSeq *Core::getVideoSeq() {
    return m_VSeq;
}
