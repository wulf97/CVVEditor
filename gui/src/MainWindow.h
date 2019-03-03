#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

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
private:
    Ui::MainWindow *ui;
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
