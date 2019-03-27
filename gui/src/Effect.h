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

public slots:
    void showSettings();
private:
    Ui::Effect *ui;
    GUIManager *m_gui;
    EffectList *m_effectList;
};

#endif // EFFECT_H
