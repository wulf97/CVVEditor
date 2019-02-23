#include "MainWindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    /* Загрузка стиля */
    QFile styleFile(":/res/stylesheet/style.qss");
    styleFile.open(QFile::ReadOnly);
    QString style(styleFile.readAll());
    a.setStyleSheet(style);

    return a.exec();
}
