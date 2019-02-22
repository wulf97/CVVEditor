/*
 * MainWindow отвечает за компановку виджетов в окне приложения и
 * соединение сигналов GUIManager и Core.
 */

#include <QDebug>
#include <QLayout>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "GUIManager.h"
#include "Core.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    GUIManager *guiManage = new GUIManager();
    Core *core = new Core();
    /* Получение модулей gui от GUIManager */
    Viewport *viewport = guiManage->getViewport();
    VideoControlBar *vControlBar = guiManage->getVideoControlBar();
    VideoCutterList *videoCutterList = guiManage->getVideoCutterList();
    PluginList *pluginList = guiManage->getPluginList();

    ui->setupUi(this);


    /* Объединение Core и GUIManager */
    /* Отправка сигналов */
    connect(guiManage, SIGNAL(uploadVideo(QString*)), core, SIGNAL(uploadVideo(QString*)));
    connect(guiManage, SIGNAL(playVideo()), core, SIGNAL(playVideo()));
    connect(guiManage, SIGNAL(stopVideo()), core, SIGNAL(stopVideo()));
    connect(guiManage, SIGNAL(pauseVideo()), core, SIGNAL(pauseVideo()));

    /* Получение сигналов */
    connect(core, SIGNAL(videoLen(int)), guiManage, SIGNAL(videoLen(int)));
    connect(core, SIGNAL(updateFrame(QImage*)), guiManage, SIGNAL(updateFrame(QImage*)));
    connect(core, SIGNAL(stoped()), guiManage, SIGNAL(stoped()));


    /* Проверка работы сигналов */
    vControlBar->sendSignals();
    /* Компановка виджетов */
    ui->topAria->addWidget(viewport);
    ui->topAria->addWidget(vControlBar);
    ui->bottomAria->addWidget(videoCutterList);
    ui->rightAria->addWidget(pluginList);
}

MainWindow::~MainWindow() {
    delete ui;
}
