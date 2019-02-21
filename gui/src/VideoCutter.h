#ifndef VIDEOCUTTER_H
#define VIDEOCUTTER_H

#include <QWidget>

namespace Ui {
class VideoCutter;
}

class VideoCutter : public QWidget {
    Q_OBJECT

public:
    explicit VideoCutter(QWidget *parent = nullptr);
    ~VideoCutter();
public slots:
    void videoLen(int);
signals:
    void uploadVideo(QString*);
private:
    Ui::VideoCutter *ui;
};

#endif // VIDEOCUTTER_H
