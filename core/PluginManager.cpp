#include <QPluginLoader>
#include <QDir>
#include <QDebug>

#include "PluginManager.h"
#include "Core.h"
//#include "IEffect.h"

PluginManager::PluginManager(QObject *parent) : QObject(parent) {
    m_parent = dynamic_cast<Core*>(parent);
    //m_plugins = QVector<IEffect*>(0);
}

IEffect *PluginManager::operator [](int i) {
    return m_plugins[i];
}

void PluginManager::load() {
    QDir pluginDir = QDir::currentPath();
    QFileInfoList filesList;

    pluginDir.cd("./plugins");
    filesList = pluginDir.entryInfoList();
    for (int i = 0; i < filesList.size(); i++) {
        QPluginLoader loader(filesList[i].absoluteFilePath());
        QObject *obj = loader.instance();
        if (loader.isLoaded()) {
            IEffect *plugin = dynamic_cast<IEffect*>(obj);
            m_plugins.push_back(plugin);
            qDebug() << "Loading: " << loader.fileName() << endl;
            qDebug() << plugin->getName();
        }
    }
}

bool PluginManager::isLoaded() {
    if (m_plugins.isEmpty())
        return false;
    else
        return true;
}

int PluginManager::size(void) {
    return m_plugins.size();
}

IEffect *PluginManager::get(int i) {
    return m_plugins[i];
}

IEffect *PluginManager::getByName(QString effectName) {
   qDebug() <<  m_plugins.size();
    for (int i = 0; i < m_plugins.size(); i++) {
        if (effectName == m_plugins[i]->getName()) {
            return m_plugins[i];
        }
    }

    return nullptr;
}
