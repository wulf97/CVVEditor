#ifndef EFFECT_H
#define EFFECT_H

#include <QWidget>

class GUIManager;

namespace Ui {
class Effect;
}

class Effect : public QWidget {
    Q_OBJECT

public:
    explicit Effect(QWidget *parent = nullptr);
    ~Effect();

    void setConnection();
private:
    Ui::Effect *ui;
    GUIManager *m_parent = nullptr;
};

#endif // EFFECT_H
