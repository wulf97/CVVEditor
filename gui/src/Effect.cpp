#include "Effect.h"
#include "ui_Effect.h"

Effect::Effect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Effect)
{
    ui->setupUi(this);
}

Effect::~Effect()
{
    delete ui;
}
