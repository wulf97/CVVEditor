#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QList>
#include <QHash>

class QPluginLoader;

class Core;
//class IEffect;
#include "IEffect.h"

class PluginManager : public QObject {
    Q_OBJECT
public:
    PluginManager(QObject *parent = nullptr);

    QString operator [](int);

    void load(void);
    bool isLoaded(void);
    int size(void);
    QString get(int);
    IEffect *createByName(QString);
private:
    Core *m_parent;
    QHash<QString, QPluginLoader*> m_pluginLoaders;
    QStringList m_pluginNames;
    //QList<IEffect*> m_plugins;
    QList<IEffect*> m_instances;
};

#endif // PLUGINMANAGER_H
