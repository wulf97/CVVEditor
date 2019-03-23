#include <QPluginLoader>
#include <QDir>
#include <QDebug>

#include "PluginManager.h"

PluginManager::PluginManager(QObject *parent) : QObject(parent) {
    m_plugins = new QVector<QObject*>;
}

QObject *PluginManager::operator [](int i) {
    return m_plugins->at(i);
}

void PluginManager::load() {
    QDir pluginDir = QDir::currentPath();
    QFileInfoList filesList;

    pluginDir.cd("./plugins");
    filesList = pluginDir.entryInfoList();
    for (int i = 0; i < filesList.size(); i++) {
        QPluginLoader loader(filesList[i].absoluteFilePath());
        QObject *plugin = loader.instance();
        if (loader.isLoaded()) {
            m_plugins->push_back(plugin);
            qDebug() << "Loading: " << loader.fileName() << endl;
        }
    }
}

bool PluginManager::isLoad() {
    if (m_plugins->isEmpty())
        return false;
    else
        return true;
}

int PluginManager::size(void) {
    return m_plugins->size();
}

QObject *PluginManager::get(int i) {
    return m_plugins->at(i);
}
