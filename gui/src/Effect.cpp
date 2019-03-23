#include "ui_Effect.h"
#include "Effect.h"
#include "GUIManager.h"

Effect::Effect(QWidget *parent) :
               QWidget(parent),
               ui(new Ui::Effect) {
    m_parent = dynamic_cast<GUIManager*>(parent);
    ui->setupUi(this);
}

Effect::~Effect() {
    delete ui;
}

void Effect::setConnection() {
    /* Подключение сигналов */
}
