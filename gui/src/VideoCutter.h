#ifndef VIDEOCUTTER_H
#define VIDEOCUTTER_H

#include <QWidget>

namespace Ui {
class VideoCutter;
}

class VideoCutter : public QWidget {
    Q_OBJECT

public:
    explicit VideoCutter(QWidget *parent = nullptr, int numberInList = 0, QString endTime = "00:00", QString videoFilePath = nullptr);
    ~VideoCutter();
    void setNumberInListValue(int);
    void setCheckBoxValue(bool);
    int getNumberInListValue();
    bool getCheckBoxValue();
    void setNumberLabel(QString);
    QString *getVideoFilePath();
    void setNameOfFile(QString);

signals:
    void uploadVideo(QString*, bool);
    void checkBoxStateChanged(int);
    void upBtn(QWidget*,QString);
    void downBtn(QWidget*,QString);

private slots:
    void on_checkBox_stateChanged(int arg1);
    void on_upBtn_clicked();
    void on_downBtn_clicked();

private:
    Ui::VideoCutter *ui;
    QString videoFilePath = nullptr;
    int numberInList = 0;
};

#endif // VIDEOCUTTER_H
