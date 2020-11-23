#ifndef VIDEO_SETTINGS_H
#define VIDEO_SETTINGS_H

#include <QWidget>
#include "ui_VideoSettings.h"

namespace Ui {
class VideoSettings;
}

class RangeSlider;

class VideoSettings : public QWidget {
    Q_OBJECT
public:
    VideoSettings(QWidget *parent = nullptr);
    ~VideoSettings();

    Ui::VideoSettings *getUi() const;
    RangeSlider *getRangeSlider() const;

private slots:
    void addVideo();

private:
    void resizeEvent(QResizeEvent *event);

signals:
    void openVideo(QString);
    void windowResize();

private:
    Ui::VideoSettings *ui;
    RangeSlider *m_rangeSlider;
    QString m_path;
};

#endif // VIDEO_SETTINGS_H
