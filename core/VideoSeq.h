#ifndef VIDEOSEQ_H
#define VIDEOSEQ_H

#include <QObject>
#include <QString>
#include <QList>

class VideoSeq : public QObject {
    Q_OBJECT
public:
    VideoSeq(QObject *parent = nullptr);
public slots:
    void addToSeq(QString, int, int);
    void clearSeq();
    void loadSeq();
    void unloadSeq();
};

#endif // VIDEOSEQ_H
