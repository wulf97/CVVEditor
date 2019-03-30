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

QString PluginManager::operator [](int i) {
    return m_pluginNames[i];
}

void PluginManager::load() {
    QDir pluginDir = QDir::currentPath();
    QFileInfoList filesList;

    pluginDir.cd("./plugins");
    filesList = pluginDir.entryInfoList();
    for (int i = 0; i < filesList.size(); i++) {
        QPluginLoader *loader = new QPluginLoader(filesList[i].absoluteFilePath());
        if (loader->isLoaded()) {
            QObject *obj = loader->instance();
            IEffect *plugin = dynamic_cast<IEffect*>(obj);
            m_pluginLoaders[plugin->getName()] = loader;
            m_pluginNames.push_back(plugin->getName());

            qDebug() << "Loading: " << loader->fileName() << endl;
            qDebug() << plugin->getName();
            delete obj;
        }
    }
}

bool PluginManager::isLoaded() {
    if (m_pluginLoaders.isEmpty())
        return false;
    else
        return true;
}

int PluginManager::size(void) {
    return m_pluginNames.size();
}

QString PluginManager::get(int i) {
    return m_pluginNames[i];
}

IEffect *PluginManager::createByName(QString effectName) {
    if (!m_pluginLoaders[effectName]) {
        QObject *obj = m_pluginLoaders[effectName]->instance();
        IEffect *effect = dynamic_cast<IEffect*>(obj);
        m_instances.push_back(effect);
    } else {
        return nullptr;
    }
}
