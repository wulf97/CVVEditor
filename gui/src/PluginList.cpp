#include <QDebug>
#include <QLayout>
#include <QPushButton>

#include "PluginList.h"
#include "ui_PluginList.h"

PluginList::PluginList(QWidget *parent) :
                       QWidget(parent),
                       ui(new Ui::PluginList) {
    ui->setupUi(this);

    QVBoxLayout *layout = new QVBoxLayout();

    this->setLayout(layout);
}

PluginList::~PluginList() {
    delete ui;
}
