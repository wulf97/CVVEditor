#include <QBoxLayout>
#include <opencv2/core.hpp>

#include "ui_Median.h"
#include "Median.h"

using namespace cv;

Median::Median(QWidget *parent) :
               QWidget(parent),
               ui(new Ui::Median) {
    ui->setupUi(this);
}

Median::~Median() {
    delete ui;
}

int Median::getID() const {
    return 1;
}

QString Median::getName() const {
    return "Median";
}

void Median::display(QBoxLayout *layout) {
    layout->addWidget(this);
}

void Median::handle(Mat &img) {

}
