#include <QDebug>
#include <QLayout>
#include <QPushButton>

#include "ui_PluginList.h"
#include "PluginList.h"

PluginList::PluginList(QWidget *parent) :
                       QWidget(parent),
                       ui(new Ui::PluginList) {
    ui->setupUi(this);
}

PluginList::~PluginList() {
    delete ui;
}
