#ifndef EFFECT_H
#define EFFECT_H
#include <QWidget>

class GUIManager;

namespace Ui {
class EffectList;
}


class EffectList : public QWidget {
    Q_OBJECT

public:
    explicit EffectList(QWidget *parent = nullptr);
    ~EffectList();

    void setConnection();
    void setEffectList(QString item);
    void addNewEffect(QString);
private:
    Ui::EffectList *ui;
    GUIManager *m_parent = nullptr;
};

#endif // EFFECT_H
