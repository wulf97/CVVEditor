#ifndef EFFECTSETTINGS_H
#define EFFECTSETTINGS_H

#include <QWidget>
#include <QHBoxLayout>

class GUIManager;
class QBoxLayout;

namespace Ui {
class EffectSettings;
}

class EffectSettings : public QWidget {
    Q_OBJECT

public:
    explicit EffectSettings(QWidget *parent = nullptr);
    ~EffectSettings();

    QBoxLayout *getDisplayLayout();
signals:
    void displayEffectsSettings(QString, QBoxLayout*);
private:
    Ui::EffectSettings *ui;
    GUIManager *m_gui;
};

#endif // EFFECTSETTINGS_H
