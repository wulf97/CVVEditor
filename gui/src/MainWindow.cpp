/*
 * MainWindow отвечает за компановку виджетов в окне приложения и
 * соединение сигналов GUIManager и Core.
 */

#include <QDebug>
#include <QLayout>
#include <QProgressBar>
#include <QTabWidget>

#include "ui_MainWindow.h"
#include "MainWindow.h"
#include "GUIManager.h"
#include "Core.h"

MainWindow::MainWindow(QWidget *parent) :
                       QMainWindow(parent),
                       ui(new Ui::MainWindow) {
    m_core = new Core();
    m_gui = new GUIManager();
    /* Получение модулей gui от GUIManager */
    m_viewport = m_gui->getViewport();
    m_vControlBar = m_gui->getVideoControlBar();
    m_videoCutterList = m_gui->getVideoCutterList();
    m_effectRangeList = m_gui->getEffectRangeList();
    m_pluginList = m_gui->getPluginList();

    m_progress = new QProgressBar(this);

    ui->setupUi(this);

    m_progress->setValue(0);
    m_progress->hide();
    /* Компановка виджетов */
    ui->topAria->addWidget(m_viewport);
    ui->topAria->addWidget(m_vControlBar);
    ui->videoCutterLayout->addWidget(m_videoCutterList);
    ui->effectCutterLayout->addWidget(m_effectRangeList);
    ui->PluginListLayout->addWidget(m_pluginList);
    ui->statusBar->addPermanentWidget(m_progress, 1);

    addMenu();
    setConnection();
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::setConnection() {
    /* Объединение m_core и GUIManager */
    /* Отправка сигналов */
    connect(m_gui, SIGNAL(uploadVideo(QString*, bool)), m_core, SIGNAL(uploadVideo(QString*, bool)));
    connect(m_gui, SIGNAL(unloadVideo()), m_core, SIGNAL(unloadVideo()));
    connect(m_gui, SIGNAL(playVideo()), m_core, SIGNAL(playVideo()));
    connect(m_gui, SIGNAL(stopVideo()), m_core, SIGNAL(stopVideo()));
    connect(m_gui, SIGNAL(pauseVideo()), m_core, SIGNAL(pauseVideo()));
    connect(m_gui, SIGNAL(setTime(int)), m_core, SIGNAL(setTime(int)));
    connect(m_gui, SIGNAL(setStartTime(int)), m_core, SIGNAL(setStartTime(int)));
    connect(m_gui, SIGNAL(setEndTime(int)), m_core, SIGNAL(setEndTime(int)));
    connect(m_gui, SIGNAL(addToSeq(QString,int,int)), m_core, SIGNAL(addToSeq(QString,int,int)));
    connect(m_gui, SIGNAL(clearSeq()), m_core, SIGNAL(clearSeq()));
    connect(m_gui, SIGNAL(loadSeq()), m_core, SIGNAL(loadSeq()));
    connect(m_gui, SIGNAL(unloadSeq()), m_core, SIGNAL(unloadSeq()));
    connect(m_gui, SIGNAL(saveSeq(QString)), m_core, SIGNAL(saveSeq(QString)));
    connect(m_gui, SIGNAL(getEffectsList()), m_core, SLOT(getEffectsList()));
    connect(m_gui, SIGNAL(addEffectList(QObject*,int,int)), m_core, SIGNAL(addEffectList(QObject*,int,int)));

    /* Получение сигналов */
    connect(m_core, SIGNAL(updateFrame(QImage*)), m_gui, SIGNAL(updateFrame(QImage*)));
    connect(m_core, SIGNAL(isStoped()), m_gui, SIGNAL(isStoped()));
    connect(m_core, SIGNAL(updateTime(int)), m_gui, SIGNAL(updateTime(int)));
    connect(m_core, SIGNAL(videoLen(int)), m_gui, SIGNAL(videoLen(int)));
    connect(m_core, SIGNAL(updateProgress(int)), m_gui, SIGNAL(updateProgress(int)));
    connect(m_core, SIGNAL(effectsList(QStringList)), m_gui, SIGNAL(effectsList(QStringList)));

    /* Объединение внутренних модулей gui */
    connect(m_vControlBar, SIGNAL(getVideoFilePath()), m_videoCutterList, SLOT(getVideoFilePath()));
    connect(m_videoCutterList, SIGNAL(stopVideo()), m_vControlBar, SIGNAL(stopVideo()));
    connect(m_videoCutterList, SIGNAL(setStartTime(int)), m_vControlBar, SLOT(setStartTime(int)));
    connect(m_videoCutterList, SIGNAL(setEndTime(int)), m_vControlBar, SLOT(setEndTime(int)));
    connect(m_videoCutterList, SIGNAL(setMaxValueToSlider(int)), m_vControlBar, SLOT(setSliderMaxValue(int)));
    connect(m_videoCutterList, SIGNAL(unloadVideo()), m_vControlBar, SLOT(unloadVideo()));

    connect(m_core, SIGNAL(updateProgress(int)), this, SLOT(updateProgress(int)));

    /* Сигналы меню */
    connect(m_actionPlay, SIGNAL(triggered(bool)), m_vControlBar, SIGNAL(playVideo()));
    connect(m_actionPlay, SIGNAL(triggered(bool)), this, SLOT(play()));

    connect(m_actionPause, SIGNAL(triggered(bool)), m_vControlBar, SIGNAL(pauseVideo()));
    connect(m_actionPause, SIGNAL(triggered(bool)), this, SLOT(pause()));

    connect(m_actionStop, SIGNAL(triggered(bool)), m_vControlBar, SIGNAL(stopVideo()));
    connect(m_actionStop, SIGNAL(triggered(bool)), this, SLOT(stop()));

    connect(m_actionAdd, SIGNAL(triggered(bool)), m_videoCutterList, SLOT(getVideoFilePath()));

    connect(m_actionExport, SIGNAL(triggered(bool)), m_videoCutterList,SLOT(saveFileAs()));
    connect(m_actionSave, SIGNAL(triggered(bool)), m_videoCutterList, SLOT(writeToJson()));
    connect(m_actionSaveAs, SIGNAL(triggered(bool)), m_videoCutterList, SLOT(writeToJsonAs()));
    connect(m_actionOpenProject, SIGNAL(triggered(bool)), m_videoCutterList, SLOT(readFromJson()));

    connect(m_gui, SIGNAL(playVideo()), this, SLOT(play()));
    connect(m_gui, SIGNAL(pauseVideo()), this, SLOT(pause()));
    connect(m_gui, SIGNAL(stopVideo()), this, SLOT(stop()));
    connect(m_gui, SIGNAL(unloadVideo()), this, SLOT(unloadVideo()));
    connect(m_gui, SIGNAL(isStoped()), this, SLOT(stop()));

    /* */
//    connect(this, SIGNAL(addEffectWrap(QObject*,int,int)), m_core, SIGNAL(addEffectWrap(QObject*,int,int)));
}

void MainWindow::play() {
    m_actionPlay->setDisabled(true);
    m_actionPause->setEnabled(true);
    m_actionStop->setEnabled(true);
//    emit addEffectWrap(this, 1000, 5000);
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

void MainWindow::updateProgress(int val) {
    if (m_progress->isHidden()) {
        m_progress->show();
        connect(m_core, SIGNAL(updateProgress(int)), m_progress, SLOT(setValue(int)));
    }

    if (val == 100) {
        m_progress->hide();
        disconnect(m_core, SIGNAL(updateProgress(int)), m_progress, SLOT(setValue(int)));
    }
}

void MainWindow::addMenu() {
    /* Компановка меню */
    addFileMenu();
    addVideoMenu();
}

void MainWindow::addFileMenu() {
    QMenu *menuFile = new QMenu("File", this);
    m_actionNewProject = new QAction("New Project", this);
    m_actionOpenProject = new QAction("Open Project", this);
    m_actionOpenRecent = new QAction("Open Recent", this);
    m_actionSave = new QAction("Save", this);
    m_actionSaveAs = new QAction("Save As", this);

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
    m_actionOpenProject->setDisabled(false);
    m_actionOpenRecent->setDisabled(true);
    m_actionSave->setDisabled(false);
    m_actionSaveAs->setDisabled(false);
}

void MainWindow::addVideoMenu() {
    QMenu *menuVideo = new QMenu("Video", this);
    m_actionPlay = new QAction("Play", this);
    m_actionPause = new QAction("Pause", this);
    m_actionStop = new QAction("Stop", this);
    m_actionAdd = new QAction("Add new", this);
    m_actionExport = new QAction("Export", this);

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

