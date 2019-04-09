#include <QFrame>
#include <QStyleOption>

#include "ui_Effect.h"

#include "Effect.h"
#include "EffectList.h"
#include "GUIManager.h"

Effect::Effect(QWidget *parent, QVBoxLayout *layout, QString text) :
               QWidget(parent),
               ui(new Ui::Effect) {
    m_effectList = dynamic_cast<EffectList*>(parent);
    m_gui = m_effectList->getParent()->getParent();

    ui->setupUi(this);
    ui->label_5->setStyleSheet("font: 15pt");
    ui->label_5->setText(text);

    myLayout = layout;

    connect(ui->settingsBtn, SIGNAL(released()), this, SLOT(showSettings()));
    connect(ui->deleteBtn, SIGNAL(released()), this, SLOT(deleteMe()));
    connect(ui->upBtn, SIGNAL(released()), this, SLOT(upBtnSlot()));
    connect(ui->downBtn, SIGNAL(released()), this, SLOT(downBtnSlot()));

    connect(this, SIGNAL(deleteMe(int)), m_effectList, SLOT(deleteEffect(int)));
    connect(this, SIGNAL(upBtn(QWidget*,QString)), m_effectList, SLOT(move(QWidget*,QString)));
    connect(this, SIGNAL(downBtn(QWidget*,QString)), m_effectList, SLOT(move(QWidget*,QString)));
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

QVBoxLayout *Effect::getLayout()
{
    return myLayout;
}

void Effect::showSettings() {
    qDebug() << "llllllllll";
    m_gui->getEffectSettings()->show();//->display("Canny");
    emit displayEffectSettings(m_gui->getEffectSettings()->getDisplayLayout());
}

void Effect::deleteMe()
{
    emit deleteMe(getNumInList());
}

void Effect::upBtnSlot()
{
    emit upBtn(this, "MoveUp");
}

void Effect::downBtnSlot()
{
    emit downBtn(this, "MoveDown");
}
