#include "ui_EffectList.h"
#include "EffectList.h"
#include "GUIManager.h"
#include "Effect.h"

EffectList::EffectList(QWidget *parent) :
               QWidget(parent),
               ui(new Ui::EffectList) {
    m_parent = dynamic_cast<PluginList*>(parent);
    ui->setupUi(this);
    connect(ui->addBtn, SIGNAL(released()), this, SLOT(addNewEffect()));
    connect(ui->delBtn, SIGNAL(released()), this, SLOT(deleteMeSlot()));

    connect(this, SIGNAL(deleteMe(int)), m_parent->getParent()->getPluginList(), SLOT(deleteEffectList(int)));
}

EffectList::~EffectList() {
    delete ui;
}

PluginList *EffectList::getParent() {
    return m_parent;
}

void EffectList::setConnection() {
    /* Подключение сигналов */
}

void EffectList::setEffectList(QString item)
{
    ui->comboBox->addItem(item);
}

void EffectList::setNumInList(int num)
{
    numInList = num;
}

int EffectList::getNumInList()
{
    return numInList;
}

void EffectList::addNewEffect()
{
    Effect *effect = new Effect(this, ui->comboBox->currentText());
    effect->setNumInList(listOfEffectsWidget.size());
    listOfEffectsWidget.append(effect);
    ui->effectListLayout->addWidget(effect);

    emit addEffect(effect, ui->comboBox->currentText());
}

void EffectList::deleteEffect(int num)
{
    for (auto i : listOfEffectsWidget) {
        Effect* p = dynamic_cast<Effect*>(i);
        if (p->getNumInList() == num) {
            delete p;
            listOfEffectsWidget.removeOne(p);
        }
    }

}

bool EffectList::move(QWidget *widget, QString direction)
{
    if(listOfEffectsWidget.size() > 1) {
        QVBoxLayout* myLayout = qobject_cast<QVBoxLayout*>(widget->parentWidget()->layout());
        int index = myLayout->indexOf(widget);
        if (direction == "MoveUp" && index == 0) {
            return false;
        }

        if (direction == "MoveDown" && index == myLayout->count()-1 ) {
            return false;
        }

        int newIndex;
        if(direction == "MoveUp") {
             newIndex = index - 1;
        } else {
            newIndex = index + 1;
        }

        myLayout->removeWidget(widget);
        myLayout->insertWidget(newIndex , widget);

        for (auto i : listOfEffectsWidget) {
            Effect* p = dynamic_cast<Effect*>(i);
            if(p->getNumInList() != myLayout->indexOf(p) + 1) {
                p->setNumInList(myLayout->indexOf(p) + 1);
            }
        }
    }

    return true;
}

void EffectList::deleteMeSlot()
{
    deleteMe(getNumInList());
}
