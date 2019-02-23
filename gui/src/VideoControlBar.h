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
signals:
    void playVideo();
    void stopVideo();
    void pauseVideo();
private:
    Ui::VideoControlBar *ui;
};

#endif // VIDEOCONTROLBAR_H
