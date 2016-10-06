#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <QFileSystemWatcher>
#include <QFile>

class FileWatcher : public QFileSystemWatcher
{
    Q_OBJECT

public:
    FileWatcher(QString path = "");
    ~FileWatcher();
    void watch(QString path);

public slots:
    void sl_fileChanged(QString path);

signals:
    void fileContentChanged(const QString content);

private:
    QString _filePath;
};

#endif // FILEWATCHER_H
