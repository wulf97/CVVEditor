#include <QDebug>
#include <QFileDialog>

#include "VideoSettings.h"
#include "RangeSlider.h"

VideoSettings::VideoSettings(QWidget *parent) : QWidget(parent) {
    ui = new Ui::VideoSettings();
    m_rangeSlider = new RangeSlider(this);
    ui->setupUi(this);

    ui->rangeSliderLayout->addWidget(m_rangeSlider);

    connect(ui->addVideoButton, SIGNAL(released()), this, SLOT(addVideo()));
}

VideoSettings::~VideoSettings() {
    delete ui;
}

Ui::VideoSettings *VideoSettings::getUi() const {
    return ui;
}

RangeSlider *VideoSettings::getRangeSlider() const {
    return m_rangeSlider;
}

void VideoSettings::addVideo() {
    m_path = QFileDialog::getOpenFileName(this, tr("Open video"), "/home/alexej/Videos", tr("Video (*.avi *.mp4 *.wmv *.mov *.mpeg *.flv)"));

    ui->videoPathLineEdit->setText(m_path);

    if (m_path != "") {
        ui->spinBox->setEnabled(true);
        emit openVideo(m_path);
    }
}

void VideoSettings::resizeEvent(QResizeEvent *event) {
    emit windowResize();
}
