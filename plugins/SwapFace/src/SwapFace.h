#ifndef SWAPFACE_H
#define SWAPFACE_H

#include <QWidget>

#include "IEffect.h"

namespace Ui {
class SwapFace;
}

class SwapFace: public QWidget, public IEffect {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Interface_id")
    Q_INTERFACES(IEffect)
public:
    explicit SwapFace(QWidget *parent = nullptr);
    ~SwapFace();

    int getID() const;
    QString getName() const;
    void display(QBoxLayout*);
    void handle(cv::Mat&);
private:
    Ui::SwapFace *ui;
};

#endif // SWAPFACE_H
