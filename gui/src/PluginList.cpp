#include <QDebug>

#include "PluginList.h"
#include "ui_PluginList.h"

PluginList::PluginList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PluginList) {
    ui->setupUi(this);
}

PluginList::~PluginList() {
    delete ui;
}
