#ifndef EFFECT_RANGE_LIST_H
#define EFFECT_RANGE_LIST_H

#include <QWidget>
#include <QVBoxLayout>

class GUIManager;
class EffectRange;

class EffectRangeList : public QWidget {
    Q_OBJECT

public:
    explicit EffectRangeList(QWidget *parent = nullptr);
    ~EffectRangeList();

    void setConnection();
public slots:
    void addNewEffectRange(int);
    void updateEndTime(int time);
    void deleteEffectRange(int);

private:
    GUIManager *m_parent = nullptr;
    int endTimeOfVideo = 0;
    QVBoxLayout *layout = new QVBoxLayout();
    QList<EffectRange*> listOfEffectRangeWidget;
};

#endif // EFFECT_RANGE_LIST_H
