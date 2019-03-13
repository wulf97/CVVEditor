#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>

class Core;

namespace Ui {
class MainWindow;
}

/**
 * @brief Класс MainWindow отвечает за компановку виджетов.
 *
 * Также MainWindow связывает Core и GUIManager.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void play();
    void pause();
    void stop();
    void unloadVideo();
    void progress(int);
private:
    Ui::MainWindow *ui;
    Core *m_core = nullptr;
    QProgressBar *m_progress = nullptr;
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
