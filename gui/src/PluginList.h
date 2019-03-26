#ifndef PLUGINLIST_H
#define PLUGINLIST_H

#include <QWidget>

class GUIManager;

namespace Ui {
class PluginList;
}

class EffectList;
class PluginList : public QWidget {
    Q_OBJECT

public:
    explicit PluginList(QWidget *parent = nullptr);
    ~PluginList();
public slots:
    void addEffectList();
private:
    Ui::PluginList *ui;
    GUIManager *m_parent;
    QList<EffectList*> listOfEffectList;

};

#endif // PLUGINLIST_H
