#ifndef CANNY_H
#define CANNY_H

#include <QWidget>

#include "IFilter.h"

namespace Ui {
class Canny;
}

class Canny: public QWidget, public IFilter {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Interface_id")
    Q_INTERFACES(IFilter)
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
