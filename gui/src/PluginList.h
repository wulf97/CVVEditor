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

    GUIManager *getParent();
public slots:
    void addEffectList();
    void setEffectsToEffectList(QStringList);
    void deleteEffectList(int);
signals:
    void addNewEffectRange(int);
    void deleteEffectRange(int);

    void addEffectList(QObject*, int, int);
private:
    Ui::PluginList *ui;
    GUIManager *m_parent;
    QList<EffectList*> listOfEffectList;

};

#endif // PLUGINLIST_H
