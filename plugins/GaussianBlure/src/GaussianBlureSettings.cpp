#include <QDebug>
#include <QFileDialog>

#include "GaussianBlureSettings.h"

GaussianBlureSettings::GaussianBlureSettings(QWidget *parent) : QWidget(parent) {
    ui = new Ui::GaussianBlureSettings();
    ui->setupUi(this);

    ui->sigma->valueChanged(3);

    connect(ui->blurRadius, SIGNAL(valueChanged(int)), this, SLOT(setBlurRadius(int)));
    connect(ui->sigma, SIGNAL(valueChanged(int)), this, SLOT(setSigma(int)));
}

GaussianBlureSettings::~GaussianBlureSettings() {
    delete ui;
}

Ui::GaussianBlureSettings *GaussianBlureSettings::getUi() const {
    return ui;
}

int GaussianBlureSettings::getBlurRadius() {
    return m_blurRadius;
}

int GaussianBlureSettings::getSigma() {
    return m_sigma;
}

void GaussianBlureSettings::setBlurRadius(int blurRadius) {
    m_blurRadius = blurRadius;
}

void GaussianBlureSettings::setSigma(int sigma) {
    m_sigma = sigma;
}
