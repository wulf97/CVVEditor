#ifndef EFFECTRANGE_H
#define EFFECTRANGE_H

#include <QWidget>

class GUIManager;
class RangeSlider;

namespace Ui {
class EffectRange;
}

class EffectRange : public QWidget {
    Q_OBJECT

public:
    explicit EffectRange(QWidget *parent = nullptr, int endTime = 0);
    ~EffectRange();

    void setMaximumValue(int);
    int getMaximumValue();

    void setMinimumValue(int);
    int getMinimumValue();

    void setNumberLabel(QString);
    int getLengthOfVideo();
    void setLenghtOfVideo(int);

    void setConnection();
    void updateEndTime(int time);
    QString intTimeToStringTime(int time);
private:
    Ui::EffectRange *ui;
    GUIManager *m_parent = nullptr;
    RangeSlider* m_RangeSlider = nullptr;
    int upperValue = 0;
    int lowerValue = 0;
};

#endif // EFFECTRANGE_H
