#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QVector>

class Core;
//class IEffect;
#include "IEffect.h"

class PluginManager : public QObject {
    Q_OBJECT
public:
    PluginManager(QObject *parent = nullptr);

    IEffect *operator [](int);

    void load(void);
    bool isLoaded(void);
    int size(void);
    IEffect *get(int);
    IEffect *getByName(QString);
private:
    Core *m_parent;
    QVector<IEffect*> m_plugins;
};

#endif // PLUGINMANAGER_H
