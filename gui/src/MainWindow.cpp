/*
 * MainWindow отвечает за компановку виджетов в окне приложения.
 */

#include <QDebug>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "GUIManager.h"
#include "Core.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    GUIManager *guiManage = new GUIManager();
    Core *core = new Core();
    /* Создание модулей gui */
    Viewport *viewport = guiManage->getViewport();
    VideoControlBar *vControlBar = guiManage->getVideoControlBar();
    VideoCutterList *videoCutterList = guiManage->getVideoCutterList();
    PluginList *pluginList = guiManage->getPluginList();

    ui->setupUi(this);

    /* Объединение Core и GUIManager */
    guiManage->setCore(core);
    core->setGUI(guiManage);

    /* Компановка виджетов */

}

MainWindow::~MainWindow() {
    delete ui;
}
