#ifndef EFFECT_H
#define EFFECT_H

#include <QWidget>

class GUIManager;
class EffectList;

namespace Ui {
class Effect;
}

class Effect : public QWidget
{
    Q_OBJECT

public:
    explicit Effect(QWidget *parent = nullptr, QString text = "");
    ~Effect();
    void setNumInList(int);
    int getNumInList();

public slots:
    void showSettings();
    void deleteMe();
signals:
    void deleteMe(int);
private:
    Ui::Effect *ui;
    GUIManager *m_gui;
    EffectList *m_effectList;
    int numInList;
};

#endif // EFFECT_H
