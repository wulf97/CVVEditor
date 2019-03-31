#include <QDebug>

#include "Core.h"
#include "IEffect.h"

Core::Core(QObject *parent) : QObject(parent) {
    QStringList effects;
    m_pManager = new PluginManager(this);
    m_VLoader = new VideoLoader(this);
    m_VSeq = new VideoSeq(this);

    m_pManager->load();
}

PluginManager *Core::getPluginManager() {
    return m_pManager;
}

VideoLoader *Core::getVideoLoader() {
    return m_VLoader;
}

VideoSeq *Core::getVideoSeq() {
    return m_VSeq;
}

//void Core::displaySettings(QString effectName, QBoxLayout *layout) {
//    qDebug() << "slot displaySettings(QString, QBoxLayout*)" << endl;
//    for (int i = 0; i < m_pManager->size(); i++) {
//        if (effectName == m_pManager->get(i)->getName()) {
//            m_pManager->get(i)->display(layout);
//        }
//    }
//}

void Core::getEffectsList() {
    QStringList effects;
    for (int i = 0; i < m_pManager->size(); i++) {
        effects.push_back(m_pManager->get(i));
    }

    emit effectsList(effects);
}
