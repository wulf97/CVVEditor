#ifndef EFFECT_H
#define EFFECT_H

#include <QWidget>

namespace Ui {
class Effect;
}

class Effect : public QWidget
{
    Q_OBJECT

public:
    explicit Effect(QWidget *parent = nullptr, QString text = "");
    ~Effect();

private:
    Ui::Effect *ui;
};

#endif // EFFECT_H
