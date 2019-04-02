#include <QBoxLayout>

#include "ui_Canny.h"
#include "Canny.h"

using namespace cv;

Canny::Canny(QWidget *parent) :
             QWidget(parent),
             ui(new Ui::Canny) {
    ui->setupUi(this);
}

Canny::~Canny() {
    delete ui;
}

int Canny::getID() const {
    return 0;
}

QString Canny::getName() const {
    return "Canny";
}

void Canny::display(QBoxLayout *layout) {
    if (this->isHidden()) {
        this->show();
    }
    layout->addWidget(this);
}

void Canny::handle(Mat &frame) {
    if (frame.channels() == 3) {
        cvtColor(frame, frame, CV_BGR2GRAY);
    }

    cv::Canny(frame, frame, ui->tresholdSpinbox->value(),
              ui->tresholdSpinbox->value()*ui->ratioSpinbox->value(),
              ui->kernalSizeSpinbox->value());
}
