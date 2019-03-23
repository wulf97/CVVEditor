#include "ui_EffectRange.h"
#include "EffectRange.h"
#include "GUIManager.h"

EffectRange::EffectRange(QWidget *parent) :
                         QWidget(parent),
                         ui(new Ui::EffectRange) {
    m_parent = dynamic_cast<GUIManager*>(parent);
    ui->setupUi(this);
}

EffectRange::~EffectRange() {
    delete ui;
}

void EffectRange::setConnection() {
    /* Подключение сигналов */
}
