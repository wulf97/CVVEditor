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
public slots:
    void stoped();
    void setStartTime(int);
    void setEndTime(int);
signals:
    /* Сигналы для для внешних модулей */
    void playVideo();
    void stopVideo();
    void pauseVideo();
    void setTime(int);

    /* Сигналы для внутренних модулей */
    void getVideoFilePath();
private:
    Ui::VideoControlBar *ui;
    int m_startTime = 0;
    int m_endTime = 0;
};

#endif // VIDEOCONTROLBAR_H
