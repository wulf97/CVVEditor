#ifndef PLUGINLIST_H
#define PLUGINLIST_H

#include <QWidget>

namespace Ui {
class PluginList;
}

class PluginList : public QWidget {
    Q_OBJECT

public:
    explicit PluginList(QWidget *parent = nullptr);
    ~PluginList();

private:
    Ui::PluginList *ui;
};

#endif // PLUGINLIST_H
