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
    GUIManager *guiManage = new GUIManager();
    m_core = new Core();
    /* Получение модулей gui от GUIManager */
    Viewport *viewport = guiManage->getViewport();
    VideoControlBar *vControlBar = guiManage->getVideoControlBar();
    VideoCutterList *videoCutterList = guiManage->getVideoCutterList();
    EffectRangeList *effectRangeList = guiManage->getEffectRangeList();
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

    m_progress = new QProgressBar(this);

    ui->setupUi(this);

    /* Объединение m_core и GUIManager */
    /* Отправка сигналов */
    connect(guiManage, SIGNAL(uploadVideo(QString*, bool)), m_core, SIGNAL(uploadVideo(QString*, bool)));
    connect(guiManage, SIGNAL(unloadVideo()), m_core, SIGNAL(unloadVideo()));
    connect(guiManage, SIGNAL(playVideo()), m_core, SIGNAL(playVideo()));
    connect(guiManage, SIGNAL(stopVideo()), m_core, SIGNAL(stopVideo()));
    connect(guiManage, SIGNAL(pauseVideo()), m_core, SIGNAL(pauseVideo()));
    connect(guiManage, SIGNAL(setTime(int)), m_core, SIGNAL(setTime(int)));
    connect(guiManage, SIGNAL(setStartTime(int)), m_core, SIGNAL(setStartTime(int)));
    connect(guiManage, SIGNAL(setEndTime(int)), m_core, SIGNAL(setEndTime(int)));
    connect(guiManage, SIGNAL(addToSeq(QString,int,int)), m_core, SIGNAL(addToSeq(QString,int,int)));
    connect(guiManage, SIGNAL(clearSeq()), m_core, SIGNAL(clearSeq()));
    connect(guiManage, SIGNAL(loadSeq()), m_core, SIGNAL(loadSeq()));
    connect(guiManage, SIGNAL(unloadSeq()), m_core, SIGNAL(unloadSeq()));
    connect(guiManage, SIGNAL(saveSeq(QString)), m_core, SIGNAL(saveSeq(QString)));
    connect(guiManage, SIGNAL(displayEffectsSettings(QString,QBoxLayout*)),
            m_core, SIGNAL(displayEffectsSettings(QString,QBoxLayout*)));
    connect(guiManage, SIGNAL(getEffectsList()), m_core, SLOT(getEffectsList()));

    /* Получение сигналов */
    connect(m_core, SIGNAL(updateFrame(QImage*)), guiManage, SIGNAL(updateFrame(QImage*)));
    connect(m_core, SIGNAL(isStoped()), guiManage, SIGNAL(isStoped()));
    connect(m_core, SIGNAL(updateTime(int)), guiManage, SIGNAL(updateTime(int)));
    connect(m_core, SIGNAL(videoLen(int)), guiManage, SIGNAL(videoLen(int)));
    connect(m_core, SIGNAL(updateProgress(int)), guiManage, SIGNAL(updateProgress(int)));
    connect(m_core, SIGNAL(effectsList(QStringList)), guiManage, SIGNAL(effectsList(QStringList)));

    /* Объединение внутренних модулей gui */
    connect(vControlBar, SIGNAL(getVideoFilePath()), videoCutterList, SLOT(getVideoFilePath()));
    connect(videoCutterList, SIGNAL(stopVideo()), vControlBar, SIGNAL(stopVideo()));
    connect(videoCutterList, SIGNAL(setStartTime(int)), vControlBar, SLOT(setStartTime(int)));
    connect(videoCutterList, SIGNAL(setEndTime(int)), vControlBar, SLOT(setEndTime(int)));
    connect(videoCutterList, SIGNAL(setMaxValueToSlider(int)), vControlBar,SLOT(setSliderMaxValue(int)));
    connect(videoCutterList, SIGNAL(unloadVideo()), vControlBar, SLOT(unloadVideo()));

    connect(m_core, SIGNAL(updateProgress(int)), this, SLOT(updateProgress(int)));

    /* Сигналы меню */
    connect(m_actionPlay, SIGNAL(triggered(bool)), vControlBar, SIGNAL(playVideo()));
    connect(m_actionPlay, SIGNAL(triggered(bool)), this, SLOT(play()));

    connect(m_actionPause, SIGNAL(triggered(bool)), vControlBar, SIGNAL(pauseVideo()));
    connect(m_actionPause, SIGNAL(triggered(bool)), this, SLOT(pause()));

    connect(m_actionStop, SIGNAL(triggered(bool)), vControlBar, SIGNAL(stopVideo()));
    connect(m_actionStop, SIGNAL(triggered(bool)), this, SLOT(stop()));

    connect(m_actionAdd, SIGNAL(triggered(bool)), videoCutterList, SLOT(getVideoFilePath()));

    connect(m_actionExport, SIGNAL(triggered(bool)), videoCutterList,SLOT(saveFileAs()));
    connect(m_actionSave, SIGNAL(triggered(bool)), videoCutterList, SLOT(writeToJson()));
    connect(m_actionSaveAs, SIGNAL(triggered(bool)), videoCutterList, SLOT(writeToJsonAs()));
    connect(m_actionOpenProject, SIGNAL(triggered(bool)), videoCutterList, SLOT(readFromJson()));

    connect(guiManage, SIGNAL(playVideo()), this, SLOT(play()));
    connect(guiManage, SIGNAL(pauseVideo()), this, SLOT(pause()));
    connect(guiManage, SIGNAL(stopVideo()), this, SLOT(stop()));
    connect(guiManage, SIGNAL(unloadVideo()), this, SLOT(unloadVideo()));
    connect(guiManage, SIGNAL(isStoped()), this, SLOT(stop()));

    m_progress->setValue(0);
    m_progress->hide();
    /* Компановка виджетов */
    ui->topAria->addWidget(viewport);
    ui->topAria->addWidget(vControlBar);
    ui->videoCutterLayout->addWidget(videoCutterList);
    ui->effectCutterLayout->addWidget(effectRangeList);
    ui->PluginListLayout->addWidget(pluginList);
    ui->statusBar->addPermanentWidget(m_progress, 1);

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
    m_actionOpenProject->setDisabled(false);
    m_actionOpenRecent->setDisabled(true);
    m_actionSave->setDisabled(false);
    m_actionSaveAs->setDisabled(false);

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



    /************/
    connect(guiManage, SIGNAL(effectsList(QStringList)), this, SLOT(bla(QStringList)));

    connect(this, SIGNAL(displayEffectsSettings(QString,QBoxLayout*)),
            guiManage, SIGNAL(displayEffectsSettings(QString,QBoxLayout*)));

//    QWidget *win = new QWidget();
//    QHBoxLayout *l = new QHBoxLayout();
//    emit displayEffectsSettings("Canny", l);

//    win->setLayout(l);
//    win->show();
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

void MainWindow::bla(QStringList) {
   qDebug() << "GGGGGGGGGGGGGGGG";
}
