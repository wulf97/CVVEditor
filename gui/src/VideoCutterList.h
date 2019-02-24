#ifndef VIDEOCUTTERLIST_H
#define VIDEOCUTTERLIST_H

#include <QWidget>

namespace Ui {
class VideoCutterList;
}

class VideoCutterList : public QWidget {
    Q_OBJECT

public:
    explicit VideoCutterList(QWidget *parent = nullptr);
    ~VideoCutterList();

signals:
    void uploadVideo(QString*);
public slots:
    void getVideoFilePath();
    void videoLen(int);
private:
    Ui::VideoCutterList *ui;
};

#endif // VIDEOCUTTERLIST_H
