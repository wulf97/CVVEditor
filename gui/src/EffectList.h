#ifndef EFFECT_LIST_H
#define EFFECT_LIST_H
#include <QWidget>

class GUIManager;

namespace Ui {
class EffectList;
}

class PluginList;
class Effect;

class EffectList : public QWidget {
    Q_OBJECT

public:
    explicit EffectList(QWidget *parent = nullptr);
    ~EffectList();

    PluginList *getParent();
    void setConnection();
    void setEffectList(QString item);
public slots:
    void addNewEffect();
    void deleteEffect(int num);
private:
    Ui::EffectList *ui;
    PluginList *m_parent = nullptr;
    QList<Effect*> listOfEffectsWidget;
};

#endif // EFFECT_LIST_H
