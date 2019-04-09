#ifndef EFFECT_H
#define EFFECT_H

#include <QWidget>
#include <QBoxLayout>

class GUIManager;
class EffectList;

namespace Ui {
class Effect;
}

class Effect : public QWidget
{
    Q_OBJECT

public:
    explicit Effect(QWidget *parent = nullptr, QVBoxLayout *layout = nullptr, QString text = "");
    ~Effect();
    void setNumInList(int);
    int getNumInList();
    QVBoxLayout *getLayout();

public slots:
    void showSettings();
    void deleteMe();
    void upBtnSlot();
    void downBtnSlot();
signals:
    void deleteMe(int);
    void upBtn(QWidget*,QString);
    void downBtn(QWidget*,QString);
    void displayEffectSettings(QBoxLayout*);
    void delEffect();
private:
    Ui::Effect *ui;
    GUIManager *m_gui;
    EffectList *m_effectList;
    int numInList;
    QVBoxLayout *myLayout;
};

#endif // EFFECT_H
