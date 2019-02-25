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
    connect(guiManage, SIGNAL(uploadVideo(QString*, bool)), core, SIGNAL(uploadVideo(QString*, bool)));
    connect(guiManage, SIGNAL(playVideo()), core, SIGNAL(playVideo()));
    connect(guiManage, SIGNAL(stopVideo()), core, SIGNAL(stopVideo()));
    connect(guiManage, SIGNAL(pauseVideo()), core, SIGNAL(pauseVideo()));
    connect(guiManage, SIGNAL(setTime(int)), core, SIGNAL(setTime(int)));
    connect(guiManage, SIGNAL(setStartTime(int)), core, SIGNAL(setStartTime(int)));
    connect(guiManage, SIGNAL(setEndTime(int)), core, SIGNAL(setEndTime(int)));

    /* Получение сигналов */
    connect(core, SIGNAL(videoLen(int)), guiManage, SIGNAL(videoLen(int)));
    connect(core, SIGNAL(updateFrame(QImage*)), guiManage, SIGNAL(updateFrame(QImage*)));
    connect(core, SIGNAL(stoped()), guiManage, SIGNAL(stoped()));

    /* Объединение внутренних модулей gui */
    connect(vControlBar, SIGNAL(getVideoFilePath()),videoCutterList, SLOT(getVideoFilePath()));

    /* Проверка работы сигналов */
//    core->testSignals();
//    guiManage->testSignals();

    /* Компановка виджетов */
    ui->topAria->addWidget(viewport);
    ui->topAria->addWidget(vControlBar);
    ui->videoCutterLayout->addWidget(videoCutterList);
    ui->PluginListLayout->addWidget(pluginList);
}

MainWindow::~MainWindow() {
    delete ui;
}
