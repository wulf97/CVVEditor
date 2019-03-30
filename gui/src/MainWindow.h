#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>

class Core;
class GUIManager;
class Viewport;
class VideoControlBar;
class VideoCutterList;
class EffectRangeList;
class PluginList;
class QBoxLayout;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setConnection();
private slots:
    void play();
    void pause();
    void stop();
    void unloadVideo();
    void updateProgress(int);
signals:
    void displayEffectsSettings(QString, QBoxLayout*);
    void addEffectWrap(QObject*, int, int);
private:
    void addMenu();
    void addFileMenu();
    void addVideoMenu();
private:
    Ui::MainWindow *ui;
    Core *m_core;
    GUIManager *m_gui;
    Viewport *m_viewport;
    VideoControlBar *m_vControlBar;
    VideoCutterList *m_videoCutterList;
    EffectRangeList *m_effectRangeList;
    PluginList *m_pluginList;

    QProgressBar *m_progress;
    /* Меню */
    /* Меню File */
    QAction *m_actionNewProject;
    QAction *m_actionOpenProject;
    QAction *m_actionOpenRecent;
    QAction *m_actionSave;
    QAction *m_actionSaveAs;
    /* Меню Video */
    QAction *m_actionPlay;
    QAction *m_actionPause;
    QAction *m_actionStop;
    QAction *m_actionAdd;
    QAction *m_actionExport;
};

#endif // MAINWINDOW_H
