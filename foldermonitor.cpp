#include "FolderMonitor.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>

FolderMonitor::FolderMonitor(const QString& path, QObject* parent)
    : QObject(parent), folderPath(path)
{
    QDir dir(folderPath);
    QList<QString> files = dir.entryList(QDir::Files);
    existingFiles.clear();
    for (const QString& f : files) {
        existingFiles.insert(f);
    }

    if (!watcher.addPath(folderPath)) {
        qWarning() << "Failed to watch folder:" << folderPath;
    }

    connect(&watcher, &QFileSystemWatcher::directoryChanged,
            this, &FolderMonitor::onDirectoryChanged);

    debounceTimer.setSingleShot(true);
    connect(&debounceTimer, &QTimer::timeout,
            this, &FolderMonitor::handleDirectoryChange);
}

void FolderMonitor::onDirectoryChanged(const QString& /*path*/)
{
    if (!debounceTimer.isActive()) {
        debounceTimer.start(500);
    }
}

void FolderMonitor::handleDirectoryChange()
{
    if (!watcher.removePath(folderPath)) {
        qWarning() << "Failed to remove watch path:" << folderPath;
    }

    QDir dir(folderPath);
    QList<QString> files = dir.entryList(QDir::Files);
    QSet<QString> currentFiles;
    for (const QString& f : files) {
        currentFiles.insert(f);
    }

    // 新規ファイル検出
    QSet<QString> newFiles = currentFiles - existingFiles;

    for (const QString& fileName : newFiles) {
        QString filePath = dir.absoluteFilePath(fileName);
        emit fileDetected(filePath);

        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString contents = in.readAll();
            qDebug() << "File contents:\n" << contents;
            file.close();
        } else {
            qWarning() << "Failed to open file:" << filePath;
        }
    }

    existingFiles = currentFiles;

    QTimer::singleShot(500, this, [this]() {
        if (!watcher.addPath(folderPath)) {
            qWarning() << "Failed to re-add watch path:" << folderPath;
        }
    });
}
