#ifndef PLUGINLIST_H
#define PLUGINLIST_H

#include <QWidget>
#include <QVBoxLayout>

class GUIManager;

namespace Ui {
class PluginList;
}

class CvvINode;

class PluginList : public QWidget {
    Q_OBJECT

public:
    explicit PluginList(QWidget *parent = nullptr);
    ~PluginList();

    void blaa();

//    GUIManager *getParent();
//    void displaySettings(CvvINode *node);
private:
    Ui::PluginList *ui;
    GUIManager *m_parent;
    QVBoxLayout *m_settingsLayout;
};

#endif // PLUGINLIST_H
