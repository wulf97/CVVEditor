#ifndef CANNY_H
#define CANNY_H

#include <QWidget>

#include "IEffect.h"

namespace Ui {
class Median;
}

class Median: public QWidget, public IEffect {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Interface_id")
    Q_INTERFACES(IEffect)
public:
    explicit Median(QWidget *parent = nullptr);
    ~Median();

    int getID() const;
    QString getName() const;
    void display(QBoxLayout*);
    void handle(cv::Mat*);
private:
    Ui::Median *ui;
};

#endif // CANNY_H
