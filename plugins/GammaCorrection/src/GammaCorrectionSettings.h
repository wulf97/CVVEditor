#ifndef VIDEO_SETTINGS_H
#define VIDEO_SETTINGS_H

#include <QWidget>
#include "ui_GammaCorrectionSettings.h"

namespace Ui {
class GammaCorrectionSettings;
}

class RangeSlider;

class GammaCorrectionSettings : public QWidget {
    Q_OBJECT
public:
    GammaCorrectionSettings(QWidget *parent = nullptr);
    ~GammaCorrectionSettings();

    Ui::GammaCorrectionSettings *getUi() const;
    RangeSlider *getRangeSlider() const;

private slots:
    void addVideo();

signals:
    void openVideo(QString);
    void windowResize();

private:
    Ui::GammaCorrectionSettings *ui;
    RangeSlider *m_rangeSlider;
    QString m_path;
};

#endif // VIDEO_SETTINGS_H
