#ifndef VIDEOSEQITEM_H
#define VIDEOSEQITEM_H

#include <QObject>

class VideoSeqItem : public QObject {
    Q_OBJECT
public:
    VideoSeqItem(QObject *parent = nullptr);
public:
    QString *path = nullptr;
    int startTime = 0;
    int endTime = 0;
    int startPos = 0;
    int endPos = 0;
    bool isOpened = false;
};

#endif // VIDEOSEQITEM_H
