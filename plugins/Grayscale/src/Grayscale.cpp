#include <QBoxLayout>

#include "ui_Grayscale.h"
#include "Grayscale.h"

using namespace cv;

Grayscale::Grayscale(QWidget *parent) :
             QWidget(parent),
             ui(new Ui::Grayscale) {
    ui->setupUi(this);
}

Grayscale::~Grayscale() {
    delete ui;
}

int Grayscale::getID() const {
    return 3;
}

QString Grayscale::getName() const {
    return "Grayscale";
}

void Grayscale::display(QBoxLayout *layout) {
    layout->addWidget(this);
}

void Grayscale::handle(Mat &frame) {
    if (frame.channels() == 3) {
        cvtColor(frame, frame, CV_BGR2GRAY);
    }
}
