#ifndef VIDEOCUTTER_H
#define VIDEOCUTTER_H

#include <QWidget>
#include <RangeSlider.h>

namespace Ui {
class VideoCutter;
}

class VideoCutter : public QWidget {
    Q_OBJECT

public:
    explicit VideoCutter(QWidget *parent = nullptr, int numberInList = 0, QString endTimeString = "00:00",int endTimeNumber = 0, QString videoFilePath = nullptr);
    ~VideoCutter();

    void setMaximumValue(int);
    int getMaximumValue();

    void setMinimumValue(int);
    int getMinimumValue();

    int getCurrentLeftPosition();
    void setCurrentLeftPosition();

    //int getCurrentRightPosition();
    void setCurrentRightPosition();

    void setNumberInListValue(int);
    int getNumberInListValue();

    void setCheckBoxValue(bool);
    bool getCheckBoxValue();

    void setNumberLabel(QString);


    QString *getVideoFilePath();
    int getLengthOfVideo();

    void setNameOfFile(QString);
    void setLenghtOfVideo(int);

    bool getValueOfCheckBox();
    QString videoLen(int);
public slots:
    void onLowerValueChanged(int aLowerValue);
    void onUpperValueChanged(int aUpperValue);
    void rememberCurrentTimeOfVideo(int);
signals:
    void uploadVideo(QString*, bool);
    void setStartTime(int);
    void setEndTime(int);
    void checkBoxStateChanged(int);
    void upBtn(QWidget*,QString);
    void downBtn(QWidget*,QString);
    void sendLengthOfVideo(int);//отправка длины видео для VideoControlBar
    void sendCurrentPositionSlider(int);
    void sendNumberToDelete(int);

private slots:
    void on_checkBox_stateChanged(int arg1);
    void on_upBtn_clicked();
    void on_downBtn_clicked();
    void deleteMe();

private:
    Ui::VideoCutter *ui;
    RangeSlider* m_RangeSlider = nullptr;
    QString videoFilePath = nullptr;
    int lengthOfFilm = 0;
    int numberInList = 0;
    int upperValue = 0;
    int lowerValue = 0;
    int currentTimeInControlBar = 0;
};

#endif // VIDEOCUTTER_H
