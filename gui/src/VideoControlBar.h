#ifndef VIDEOCONTROLBAR_H
#define VIDEOCONTROLBAR_H

#include <QWidget>

namespace Ui {
class VideoControlBar;
}

class VideoControlBar : public QWidget {
    Q_OBJECT

public:
    explicit VideoControlBar(QWidget *parent = nullptr);
    ~VideoControlBar();

    void testSignals();
    void setSliderPosition(int);
public slots:
    void play();
    void pause();
    void stop();
    void stoped();
    void setStartTime(int);
    void setEndTime(int);
    void updateTime(int);
    void setSliderMaxValue(int);
signals:
    /* Сигналы для для внешних модулей */
    void playVideo();
    void stopVideo();
    void pauseVideo();
    void setTime(int);

    /* Сигналы для внутренних модулей */
    void getVideoFilePath();
private slots:
    void on_slider_sliderMoved(int position);

private:
    QString msecToTime(int);
private:
    Ui::VideoControlBar *ui;
    int m_startTime = 0;
    int m_endTime = 0;
};

#endif // VIDEOCONTROLBAR_H
