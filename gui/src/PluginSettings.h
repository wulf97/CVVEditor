#ifndef PLUGINSETTINGS_H
#define PLUGINSETTINGS_H

#include <QWidget>
#include <QVBoxLayout>

class CvvINode;

class PluginSettings : public QWidget {
public:
    PluginSettings(QWidget *parent = nullptr);
    ~PluginSettings();

    void displaySettings(CvvINode *node);

private:
   QVBoxLayout *m_settingsLayout;
};

#endif // PLUGINSETTINGS_H
