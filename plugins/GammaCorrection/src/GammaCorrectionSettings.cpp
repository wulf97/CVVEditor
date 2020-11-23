#include <QDebug>
#include <QFileDialog>

#include "GammaCorrectionSettings.h"

GammaCorrectionSettings::GammaCorrectionSettings(QWidget *parent) : QWidget(parent) {
    ui = new Ui::GammaCorrectionSettings();
    ui->setupUi(this);
}

GammaCorrectionSettings::~GammaCorrectionSettings() {
    delete ui;
}

Ui::GammaCorrectionSettings *GammaCorrectionSettings::getUi() const {
    return ui;
}
