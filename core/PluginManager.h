#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QVector>

class Core;

class PluginManager : public QObject {
    Q_OBJECT
public:
    PluginManager(QObject *parent = nullptr);

    QObject *operator [](int);

    void load(void);
    bool isLoad(void);
    int size(void);
    QObject *get(int);

private:
    Core *m_parent;
    QVector<QObject*> *m_plugins;
};

#endif // PLUGINMANAGER_H
