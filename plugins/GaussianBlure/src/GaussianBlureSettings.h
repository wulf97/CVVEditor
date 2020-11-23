#ifndef VIDEO_SETTINGS_H
#define VIDEO_SETTINGS_H

#include <QWidget>
#include "ui_GaussianBlureSettings.h"

namespace Ui {
class GaussianBlureSettings;
}

class RangeSlider;

class GaussianBlureSettings : public QWidget {
    Q_OBJECT
public:
    GaussianBlureSettings(QWidget *parent = nullptr);
    ~GaussianBlureSettings();

    Ui::GaussianBlureSettings *getUi() const;
    RangeSlider *getRangeSlider() const;

    int getBlurRadius();
    int getSigma();
private slots:
    void setBlurRadius(int);
    void setSigma(int);

signals:
    void openVideo(QString);
    void windowResize();

private:
    Ui::GaussianBlureSettings *ui;
    RangeSlider *m_rangeSlider;
    QString m_path;
    int m_blurRadius = 1;
    int m_sigma = 0;
};

#endif // VIDEO_SETTINGS_H
