#include <QDebug>

#include "Core.h"
#include "IEffect.h"

Core::Core(QObject *parent) : QObject(parent) {
    QStringList effects;
    m_VLoader = new VideoLoader(this);
    m_VSeq = new VideoSeq(this);
    m_pManager = new PluginManager(this);

    m_pManager->load();
    for (int i = 0; i < m_pManager->size(); i++) {
        qDebug() << "Filter: " << dynamic_cast<IEffect*>(m_pManager->get(i))->getName();
        effects.push_back(dynamic_cast<IEffect*>(m_pManager->get(i))->getName());
    }


    emit effectsList(effects);

    connect(this, SIGNAL(displayEffectsSettings(QString, QBoxLayout*)),
            this, SLOT(displaySettings(QString, QBoxLayout*)));
}

VideoLoader *Core::getVideoLoader() {
    return m_VLoader;
}

VideoSeq *Core::getVideoSeq() {
    return m_VSeq;
}

void Core::displaySettings(QString effectName, QBoxLayout *layout) {
    qDebug() << "slot displaySettings(QString, QBoxLayout*)" << endl;
    for (int i = 0; i < m_pManager->size(); i++) {
        IEffect *effect = dynamic_cast<IEffect*>(m_pManager->get(i));
        if (effectName == effect->getName()) {
            effect->display(layout);
        }
    }
}
