#include "EffectSettings.h"
#include "ui_EffectSettings.h"
#include "GUIManager.h"

EffectSettings::EffectSettings(QWidget *parent) :
                               ui(new Ui::EffectSettings) {
    m_gui = dynamic_cast<GUIManager*>(parent);
    ui->setupUi(this);
//    connect(this, SIGNAL(displayEffectsSettings(QString,QBoxLayout*)),
//            m_gui, SIGNAL(displayEffectsSettings(QString,QBoxLayout*)));
}

EffectSettings::~EffectSettings() {
    delete ui;
}

void EffectSettings::display(QString effectName) {
    emit displayEffectsSettings(effectName, ui->settingsLayout);
    show();
}
