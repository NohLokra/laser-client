#include "filewatcher.h"

FileWatcher::FileWatcher() : QFileSystemWatcher(), _isWatching(false)
{
}

FileWatcher::~FileWatcher()
{

}

void FileWatcher::watch(QString path) {
    if ( !this->_isWatching ) {
        this->_isWatching = true;
        bool isFileWatched = this->addPath(path);

        if ( !isFileWatched ) {
            qDebug() << "Failed to watch file " << path;

            throw QString("Failed to watch file at path %1").arg(path);
        }

        connect(this, SIGNAL(fileChanged(QString)), this, SLOT(onFileChange(QString)));
    } else {
        throw "FileWatcher already watching. Call to watch() not allowed";
    }
}

void FileWatcher::onFileChange(QString path) {
    qDebug() << "File content changed";
    QFile file(path);

    if ( !file.open(QIODevice::ReadOnly | QIODevice::Text) )
        return;

    QByteArray fileBytesContent;
    while ( !file.atEnd() ) {
        QByteArray line = file.readLine();
        fileBytesContent.append(line);
    }

    QString fileContent(fileBytesContent);

    emit fileContentChanged(fileContent);
}
