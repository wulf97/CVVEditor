#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>

class PluginManager : public QObject {
    Q_OBJECT
public:
    PluginManager(QObject *parent = nullptr);
};

#endif // PLUGINMANAGER_H
