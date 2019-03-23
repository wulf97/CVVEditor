#ifndef EFFECT_RANGE_LIST_H
#define EFFECT_RANGE_LIST_H

#include <QWidget>

class GUIManager;

class EffectRangeList : public QWidget {
    Q_OBJECT

public:
    explicit EffectRangeList(QWidget *parent = nullptr);
    ~EffectRangeList();

    void setConnection();
private:
    GUIManager *m_parent = nullptr;
};

#endif // EFFECT_RANGE_LIST_H
