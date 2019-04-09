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
    void setNumInList(int);
    int getNumInList();
public slots:
    void addNewEffect();
    void deleteEffect(int num);
    bool move(QWidget *widget, QString direction);
    void deleteMeSlot();
    void setStartTimeRange(int);
    void setStartEndRange(int);
signals:
    void deleteMe(int);
    void addEffect(QObject*, QString);
    void setEffectStartTime(int);
    void setEffectEndTime(int);
    void delEffectList();
private:
    Ui::EffectList *ui;
    PluginList *m_parent = nullptr;
    QList<Effect*> listOfEffectsWidget;
    int numInList;
    int startTimeRange;
    int endTimeRange;
};

#endif // EFFECT_LIST_H
