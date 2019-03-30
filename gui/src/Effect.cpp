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
    connect(ui->deleteBtn, SIGNAL(released()), this, SLOT(deleteMe()));
    connect(this, SIGNAL(deleteMe(int)), m_effectList, SLOT(deleteEffect(int)));
}

Effect::~Effect() {
    delete ui;
}

void Effect::setNumInList(int num)
{
    numInList = num;
}

int Effect::getNumInList()
{
    return numInList;
}

void Effect::showSettings() {
    qDebug() << "llllllllll";
    m_gui->getEffectSettings()->display("Canny");
}

void Effect::deleteMe()
{
    emit deleteMe(getNumInList());
}
