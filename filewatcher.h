#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <QFileSystemWatcher>
#include <QFile>
#include <exception>
#include <QString>
#include <QDateTime>
#ifdef QT_DEBUG
#include <QDebug>
#endif

class FileWatcher : public QFileSystemWatcher
{
    Q_OBJECT

public:
    FileWatcher();
    ~FileWatcher();
    void watch(QString path);

public slots:
    void onFileChange(QString path);

signals:
    void fileContentChanged(const QString content);

private:
    bool _isWatching;
};

#endif // FILEWATCHER_H
