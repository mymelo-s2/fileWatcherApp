#ifndef FOLDERMONITOR_H
#define FOLDERMONITOR_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QSet>
#include <QString>
#include <QTimer>

class FolderMonitor : public QObject
{
    Q_OBJECT

public:
    explicit FolderMonitor(const QString& path, QObject* parent = nullptr);

private slots:
    void onDirectoryChanged(const QString& path);
    void handleDirectoryChange();  // 実際の処理

signals:
    void fileDetected(const QString& fileName);

private:
    QString folderPath;
    QFileSystemWatcher watcher;
    QSet<QString> existingFiles;
    QTimer debounceTimer;
};

#endif // FOLDERMONITOR_H
