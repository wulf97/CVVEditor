#ifndef CORE_H
#define CORE_H

#include <QObject>

#include "VideoLoader.h"
#include "VideoSeq.h"

/**
 * @brief Класс Core связывает модули ядра с остальными модулями системы.
 *
 * Core принимает сигнылы от внешних модулей и модулей ядра, а затем перенаправляет их по цепочке.
 */
class Core : public QObject {
    Q_OBJECT
public:
    Core(QObject *parent = nullptr);

    /**
     * @brief testSignals используется для тестирования сигналов.
     */
    void testSignals();
    /**
     * @brief getVideoLoader используется для доступа к загрузчику видео.
     * @return Указатель на VideoLoader.
     */
    VideoLoader *getVideoLoader();
    /**
     * @brief getVideoSeq используется для доступа к загрузчику видеопоследовательностей.
     * @return Указатель на VideoSeq.
     */
    VideoSeq *getVideoSeq();
signals:
    /* Сигналы для внутренних модулей */
    void uploadVideo(QString*, bool);
    void unloadVideo();
    void playVideo();
    void stopVideo();
    void pauseVideo();
    void setTime(int);
    void setStartTime(int);
    void setEndTime(int);
    void addToSeq(QString, int, int);
    void clearSeq();
    void loadSeq();
    void unloadSeq();
    void saveSeq(QString);

    /* Сигналы для внешних модулей */
    void videoLen(int);
    void updateFrame(QImage*);
    void stoped();
    void updateTime(int);
    void ended();
private:
    VideoLoader *m_VLoader = nullptr;
    VideoSeq *m_VSeq = nullptr;
};

#endif // CORE_H
