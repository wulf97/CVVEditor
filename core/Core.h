#ifndef CORE_H
#define CORE_H

#include <QObject>

#include "PluginManager.h"
#include "VideoLoader.h"
#include "VideoSeq.h"


class QBoxLayout;

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
     * @brief getVideoLoader используется для доступа к загрузчику видео.
     * @return Указатель на VideoLoader.
     */
    VideoLoader *getVideoLoader();
    /**
     * @brief getVideoSeq используется для доступа к загрузчику видеопоследовательностей.
     * @return Указатель на VideoSeq.
     */
    VideoSeq *getVideoSeq();
public slots:
    void displaySettings(QString, QBoxLayout*);
    void getEffectsList();
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
    void displayEffectsSettings(QString, QBoxLayout*);

    /* Сигналы для внешних модулей */
    void videoLen(int);
    void updateFrame(QImage*);
    void isStoped();
    void updateTime(int);
    void ended();
    void updateProgress(int);
    void effectsList(QStringList);
private:
    PluginManager *m_pManager;
    VideoLoader *m_VLoader;
    VideoSeq *m_VSeq;
};

#endif // CORE_H
