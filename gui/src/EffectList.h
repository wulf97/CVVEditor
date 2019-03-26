#ifndef EFFECT_LIST_H
#define EFFECT_LIST_H
#include <QWidget>

class GUIManager;

namespace Ui {
class EffectList;
}

class Effect;

class EffectList : public QWidget {
    Q_OBJECT

public:
    explicit EffectList(QWidget *parent = nullptr);
    ~EffectList();

    void setConnection();
    void setEffectList(QString item);
public slots:
    void addNewEffect();
private:
    Ui::EffectList *ui;
    GUIManager *m_parent = nullptr;
    QList<Effect*> listOfEffectsWidget;
};

#endif // EFFECT_H
