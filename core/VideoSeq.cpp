#include <QDebug>

#include "VideoSeq.h"

VideoSeq::VideoSeq(QObject *parent) : QObject(parent) {

}

void VideoSeq::addToSeq(QString path, int startTime, int endTime) {
    qDebug() << "slot: addToSeq" << endl;
}

void VideoSeq::clearSeq() {
    qDebug() << "slot: clearSeq" << endl;
}

void VideoSeq::loadSeq() {
    qDebug() << "slot: loadSeq" << endl;
}
