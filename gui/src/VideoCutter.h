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
    void setCheckBoxValue(bool);
    int getSpinBoxValue();
    bool getCheckBoxValue();

signals:
    void uploadVideo(QString*);
    void checkBoxStateChanged(int);
private slots:
    void on_checkBox_stateChanged(int arg1);

private:
    Ui::VideoCutter *ui;
};

#endif // VIDEOCUTTER_H
