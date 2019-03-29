#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include <QWidget>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "IEffect.h"

namespace Ui {
class Grayscale;
}

class Grayscale: public QWidget, public IEffect {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Interface_id")
    Q_INTERFACES(IEffect)
public:
    explicit Grayscale(QWidget *parent = nullptr);
    ~Grayscale();

    int getID() const;
    QString getName() const;
    void display(QBoxLayout*);
    void handle(cv::Mat&);
private:
    Ui::Grayscale *ui;
};

#endif // GRAYSCALE_H
