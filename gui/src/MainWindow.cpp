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

    /* Меню */
    QMenu *menuFile = new QMenu("File", this);
    QMenu *menuVideo = new QMenu("Video", this);

    m_actionNewProject = new QAction("New Project", this);
    m_actionOpenProject = new QAction("Open Project", this);
    m_actionOpenRecent = new QAction("Open Recent", this);
    m_actionSave = new QAction("Save", this);
    m_actionSaveAs = new QAction("Save As", this);

    m_actionPlay = new QAction("Play", this);
    m_actionPause = new QAction("Pause", this);
    m_actionStop = new QAction("Stop", this);
    m_actionAdd = new QAction("Add new", this);
    m_actionExport = new QAction("Export", this);

    ui->setupUi(this);

    /* Объединение Core и GUIManager */
    /* Отправка сигналов */
    connect(guiManage, SIGNAL(uploadVideo(QString*, bool)), core, SIGNAL(uploadVideo(QString*, bool)));
    connect(guiManage, SIGNAL(unloadVideo()), core, SIGNAL(unloadVideo()));
    connect(guiManage, SIGNAL(playVideo()), core, SIGNAL(playVideo()));
    connect(guiManage, SIGNAL(stopVideo()), core, SIGNAL(stopVideo()));
    connect(guiManage, SIGNAL(pauseVideo()), core, SIGNAL(pauseVideo()));
    connect(guiManage, SIGNAL(setTime(int)), core, SIGNAL(setTime(int)));
    connect(guiManage, SIGNAL(setStartTime(int)), core, SIGNAL(setStartTime(int)));
    connect(guiManage, SIGNAL(setEndTime(int)), core, SIGNAL(setEndTime(int)));
    connect(guiManage, SIGNAL(addToSeq(QString,int,int)), core, SIGNAL(addToSeq(QString,int,int)));
    connect(guiManage, SIGNAL(clearSeq()), core, SIGNAL(clearSeq()));
    connect(guiManage, SIGNAL(loadSeq()), core, SIGNAL(loadSeq()));
    connect(guiManage, SIGNAL(unloadSeq()), core, SIGNAL(unloadSeq()));

    /* Получение сигналов */
    connect(core, SIGNAL(updateFrame(QImage*)), guiManage, SIGNAL(updateFrame(QImage*)));
    connect(core, SIGNAL(stoped()), guiManage, SIGNAL(stoped()));
    connect(core, SIGNAL(updateTime(int)), guiManage, SIGNAL(updateTime(int)));
    connect(core, SIGNAL(videoLen(int)), guiManage, SIGNAL(videoLen(int)));

    /* Объединение внутренних модулей gui */
    connect(vControlBar, SIGNAL(getVideoFilePath()), videoCutterList, SLOT(getVideoFilePath()));
    connect(videoCutterList, SIGNAL(stopVideo()), vControlBar, SIGNAL(stopVideo()));
    connect(videoCutterList, SIGNAL(setStartTime(int)), vControlBar, SLOT(setStartTime(int)));
    connect(videoCutterList, SIGNAL(setEndTime(int)), vControlBar, SLOT(setEndTime(int)));
    connect(videoCutterList, SIGNAL(setMaxValueToSlider(int)), vControlBar,SLOT(setSliderMaxValue(int)));
    connect(videoCutterList, SIGNAL(unloadVideo()), vControlBar, SLOT(unloadVideo()));

    /* Сигналы меню */
    connect(m_actionPlay, SIGNAL(triggered(bool)), vControlBar, SIGNAL(playVideo()));
    connect(m_actionPlay, SIGNAL(triggered(bool)), this, SLOT(play()));

    connect(m_actionPause, SIGNAL(triggered(bool)), vControlBar, SIGNAL(pauseVideo()));
    connect(m_actionPause, SIGNAL(triggered(bool)), this, SLOT(pause()));

    connect(m_actionStop, SIGNAL(triggered(bool)), vControlBar, SIGNAL(stopVideo()));
    connect(m_actionStop, SIGNAL(triggered(bool)), this, SLOT(stop()));

    connect(m_actionAdd, SIGNAL(triggered(bool)), videoCutterList, SLOT(getVideoFilePath()));

    connect(m_actionExport, SIGNAL(triggered(bool)), videoCutterList,SLOT(saveFileAs()));

    connect(vControlBar, SIGNAL(playVideo()), this, SLOT(play()));
    connect(vControlBar, SIGNAL(pauseVideo()), this, SLOT(pause()));
    connect(vControlBar, SIGNAL(stopVideo()), this, SLOT(stop()));
    connect(videoCutterList, SIGNAL(unloadVideo()), this, SLOT(unloadVideo()));

    /* Проверка работы сигналов */
//    core->testSignals();
//    guiManage->testSignals();

    /* Компановка виджетов */
    ui->topAria->addWidget(viewport);
    ui->topAria->addWidget(vControlBar);
    ui->videoCutterLayout->addWidget(videoCutterList);
    ui->PluginListLayout->addWidget(pluginList);

    /* Компановка меню */
    ui->menuBar->addMenu(menuFile);
    menuFile->addAction(m_actionNewProject);
    menuFile->addAction(m_actionOpenProject);
    menuFile->addAction(m_actionOpenRecent);
    menuFile->addSeparator();
    menuFile->addAction(m_actionSave);
    menuFile->addAction(m_actionSaveAs);

    m_actionNewProject->setShortcut(QKeySequence("Ctrl+n"));
    m_actionOpenProject->setShortcut(QKeySequence("Ctrl+o"));
    m_actionSave->setShortcut(QKeySequence("Ctrl+s"));
    m_actionSaveAs->setShortcut(QKeySequence("Ctrl+Shift+s"));

    m_actionNewProject->setDisabled(true);
    m_actionOpenProject->setDisabled(true);
    m_actionOpenRecent->setDisabled(true);
    m_actionSave->setDisabled(true);
    m_actionSaveAs->setDisabled(true);

    ui->menuBar->addMenu(menuVideo);
    menuVideo->addAction(m_actionPlay);
    menuVideo->addAction(m_actionPause);
    menuVideo->addAction(m_actionStop);
    menuVideo->addSeparator();
    menuVideo->addAction(m_actionAdd);
    menuVideo->addAction(m_actionExport);

    m_actionPlay->setShortcut(QKeySequence("Alt+r"));
    m_actionPause->setShortcut(QKeySequence("Alt+p"));
    m_actionStop->setShortcut(QKeySequence("Alt+s"));
    m_actionAdd->setShortcut(QKeySequence("Alt+n"));
    m_actionExport->setShortcut(QKeySequence("Alt+e"));

    m_actionPlay->setDisabled(true);
    m_actionPause->setDisabled(true);
    m_actionStop->setDisabled(true);
    m_actionExport->setDisabled(false);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::play() {
    m_actionPlay->setDisabled(true);
    m_actionPause->setEnabled(true);
    m_actionStop->setEnabled(true);
}

void MainWindow::pause() {
    m_actionPlay->setEnabled(true);
    m_actionPause->setDisabled(true);
    m_actionStop->setEnabled(true);
}

void MainWindow::stop() {
    m_actionPlay->setEnabled(true);
    m_actionPause->setDisabled(true);
    m_actionStop->setDisabled(true);
}

void MainWindow::unloadVideo() {
    m_actionPlay->setDisabled(true);
    m_actionPause->setDisabled(true);
    m_actionStop->setDisabled(true);
}
