#ifndef EFFECTRANGE_H
#define EFFECTRANGE_H

#include <QWidget>

class GUIManager;

namespace Ui {
class EffectRange;
}

class EffectRange : public QWidget {
    Q_OBJECT

public:
    explicit EffectRange(QWidget *parent = nullptr);
    ~EffectRange();

    void setConnection();
private:
    Ui::EffectRange *ui;
    GUIManager *m_parent = nullptr;
};

#endif // EFFECTRANGE_H
