#ifndef CANNY_H
#define CANNY_H

#include <QWidget>

#include "IEffect.h"

namespace Ui {
class Canny;
}

class Canny: public QWidget, public IEffect {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Interface_id")
    Q_INTERFACES(IEffect)
public:
    explicit Canny(QWidget *parent = nullptr);
    ~Canny();

    int getID() const;
    QString getName() const;
    void display(QBoxLayout*);
    void handle(cv::Mat*);
private:
    Ui::Canny *ui;
};

#endif // CANNY_H
