#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <QtPlugin>

class QBoxLayout;
class QString;
namespace cv {
class Mat;
}

class IFilter {
public:
    ~IFilter() {}
    virtual int getID() const = 0;
    virtual QString getName() const = 0;
    virtual void display(QBoxLayout*) = 0;
    virtual void handle(cv::Mat*) = 0;
};

#define Interface_iid "Interface_iid"

Q_DECLARE_INTERFACE(IFilter, Interface_iid)

#endif // IPLUGIN_H
