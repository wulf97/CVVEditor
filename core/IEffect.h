#ifndef IEFFECT_H
#define IEFFECT_H

#include <QtPlugin>

class QBoxLayout;
class QString;
namespace cv {
class Mat;
}

class IEffect {
public:
    ~IEffect() {}

    virtual int getID() const = 0;
    virtual QString getName() const = 0;
    virtual void display(QBoxLayout*) = 0;
    virtual void handle(cv::Mat&) = 0;
};

#define Interface_iid "Interface_iid"

Q_DECLARE_INTERFACE(IEffect, Interface_iid)

#endif // IEFFECT_H
