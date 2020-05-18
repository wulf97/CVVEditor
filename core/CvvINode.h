#ifndef CVVINODE_H
#define CVVINODE_H

#include <QObject>
#include <QtPlugin>

class CvvINode;
class CvvINodePort;

class CvvINodeFactory : public QObject {
public:
    ~CvvINodeFactory() {}

    // Получить имя ноды
    virtual QString getName() const = 0;
    // Получить информацию о ноде
    virtual QString getInfo() const = 0;
    // Создать новый экземпляр ноды
    virtual CvvINode *createNode() = 0;
};

class CvvINode : public QObject {
public:
    ~CvvINode() {}

    virtual void setItemName(QString) = 0;
    // Получить имя экземпляра ноды
    virtual QString getItemName() const = 0;
    // Получить список входов
    virtual QVector<CvvINodePort*> getSrc() const = 0;
    // Получить список выходов
    virtual QVector<CvvINodePort*> getDst() const = 0;
public slots:
    // Вызывается для обработки новых данных на входе
    virtual void updateNode() = 0;
};

Q_DECLARE_INTERFACE(CvvINode, "CvvINode")


#endif // CVVINODE_H
