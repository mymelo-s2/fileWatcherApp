#include "mainwindow.h"
#include "FolderMonitor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    QString watchPath = "C:/Users/xxxxx/Documents/test";
    // 動的確保してMainWindowを親に指定し、メモリ管理を任せる
    FolderMonitor* monitor = new FolderMonitor(watchPath, &w);

    QObject::connect(monitor, &FolderMonitor::fileDetected,
                     &w, &MainWindow::onFileDetected);

    return a.exec();
}
