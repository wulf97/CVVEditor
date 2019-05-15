#include "EffectViewport.h"
#include "ui_EffectViewport.h"
#include "GUIManager.h"

EffectViewport::EffectViewport(QWidget *parent) :
                               ui(new Ui::EffectViewport) {
    m_gui = dynamic_cast<GUIManager*>(parent);
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);

    connect(m_gui, SIGNAL(updateFrame(QImage*)), this, SLOT(updateFrame(QImage*)));
}

EffectViewport::~EffectViewport() {
    delete ui;
}

QBoxLayout *EffectViewport::getDisplayLayout() {
    return ui->settingsLayout;
}

void EffectViewport::updateFrame(QImage *img) {
    QImage imgg = img->copy(0, 0, img->width(), img->height());
    imgg = imgg.scaledToWidth(ui->viewport->width());
    ui->viewport->setPixmap(QPixmap::fromImage(imgg));
}
