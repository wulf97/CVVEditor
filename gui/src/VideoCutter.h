#ifndef VIDEOCUTTER_H
#define VIDEOCUTTER_H

#include <QWidget>

namespace Ui {
class VideoCutter;
}

class VideoCutter : public QWidget {
    Q_OBJECT

public:
    explicit VideoCutter(QWidget *parent = nullptr, int spinBoxValue = 0, QString endTime = "00:00");
    ~VideoCutter();
    void setSpinBoxValue(int);

signals:
    void uploadVideo(QString*);
private:
    Ui::VideoCutter *ui;
};

#endif // VIDEOCUTTER_H
