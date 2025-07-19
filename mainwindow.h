#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onFileDetected(const QString& filePath);

private:
    Ui::MainWindow *ui;
    QStringListModel* listModel;
    QStringList fileList;  // ファイル名をためるリスト
};
#endif // MAINWINDOW_H
