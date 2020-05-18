#ifndef CVVINODEPORT_H
#define CVVINODEPORT_H

#include <QObject>
#include <QVector>
#include <QDebug>

#include <opencv2/core.hpp>

#define PORT_CONFIG_DST true
#define PORT_CONFIG_SRC false

#define TYPES_NUMBER 6

#define CVV_8C      1 << 0
#define CVV_32I     1 << 1
#define CVV_32F     1 << 2
#define CVV_VEC8C   1 << 3
#define CVV_VEC32I  1 << 4
#define CVV_VEC32F  1 << 5
#define CVV_IMG8C1  1 << 6
#define CVV_IMG8C2  1 << 7
#define CVV_IMG8C3  1 << 8

typedef char T8C;
typedef int T32I;
typedef float T32F;
typedef QVector<char> Tvec8C;
typedef QVector<int> Tvec32I;
typedef QVector<float> Tvec32F;
typedef cv::Mat Timg8C1;
typedef cv::Mat Timg8C2;
typedef cv::Mat Timg8C3;

class CvvINode;

class CvvINodePort : public QObject {
    Q_OBJECT
public:
    CvvINodePort(QObject *parent = nullptr,
                 bool config = PORT_CONFIG_DST,
                 QString name = "");
    ~CvvINodePort();

    void setDataType(int);
    CvvINode *getParentNode() const;
    QString getName() const;
    int getConfig() const;
    int getDataType() const;
    int getSelectedDataType() const;
    void printMetaData();

    bool getData(int, T8C&) const;
    bool getData(int, T32I&) const;
    bool getData(int, T32F&) const;
    bool getData(int, Tvec8C*&) const;
    bool getData(int, Tvec32I*&) const;
    bool getData(int, Tvec32F*&) const;

public slots:
    void updateConnection(QObject*, bool); // Обновновить подключение к порту

    void setData(T8C);
    void setData(T32I);
    void setData(T32F);
    void setData(Tvec8C*);
    void setData(Tvec32I*);
    void setData(Tvec32F*);

signals:
    void req2Connection(QObject*, bool); // Запросить подключение у другого порта

    void sendData(T8C);
    void sendData(T32I);
    void sendData(T32F);
    void sendData(Tvec8C*);
    void sendData(Tvec32I*);
    void sendData(Tvec32F*);

private:
    bool m_config; // true - порт работает на вход, false - порт работает на выход
    int m_type; // Возможные типы данных для порта
    int m_selectedDataType; // Установленный тип порта при подключении
    QString m_name; // Название порта
    CvvINodePort *m_srcPort = nullptr; // Подключённый порт, если порт сконфигурирован на вход

    /* Значение на входе/выходе порта */
    T8C m_8C;
    T32I m_32I;
    T32F m_32F;
    Tvec8C *m_vec8C;
    Tvec32I *m_vec32I;
    Tvec32F *m_vec32F;
};

#endif // CVVINODEPORT_H
