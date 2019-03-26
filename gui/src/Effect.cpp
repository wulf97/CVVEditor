#include "Effect.h"
#include "ui_Effect.h"
#include <QFrame>
#include <QStyleOption>
#include <QPainter>

Effect::Effect(QWidget *parent, QString text) :
    QWidget(parent),
    ui(new Ui::Effect)
{
    ui->setupUi(this);
    ui->label_5->setStyleSheet("font: 15pt");
    ui->label_5->setText(text);

}

Effect::~Effect()
{
    delete ui;
}
