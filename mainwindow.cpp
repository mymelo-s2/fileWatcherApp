#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , listModel(new QStringListModel(this))
{
    ui->setupUi(this);

    // listViewにモデルをセット
    ui->listView->setModel(listModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onFileDetected(const QString& filePath)
{
    fileList.append(filePath);
    listModel->setStringList(fileList);
}
