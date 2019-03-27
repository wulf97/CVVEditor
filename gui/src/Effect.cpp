#include <QFrame>
#include <QStyleOption>

#include "ui_Effect.h"

#include "Effect.h"
#include "EffectList.h"
#include "GUIManager.h"

Effect::Effect(QWidget *parent, QString text) :
               QWidget(parent),
               ui(new Ui::Effect) {
    m_effectList = dynamic_cast<EffectList*>(parent);
    m_gui = m_effectList->getParent()->getParent();

    ui->setupUi(this);
    ui->label_5->setStyleSheet("font: 15pt");
    ui->label_5->setText(text);

    connect(ui->settingsBtn, SIGNAL(released()), this, SLOT(showSettings()));
}

Effect::~Effect() {
    delete ui;
}

void Effect::showSettings() {
    qDebug() << "llllllllll";
    m_gui->getEffectSettings()->display("Canny");
}
