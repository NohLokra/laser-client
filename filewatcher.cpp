#include "filewatcher.h"

FileWatcher::FileWatcher(QString path) : QFileSystemWatcher(), _filePath(path)
{
    connect(this, SIGNAL(fileChanged(QString)), this, SLOT(sl_fileChanged(QString)));
}

FileWatcher::~FileWatcher()
{

}

void FileWatcher::watch(QString path) {
    if ( this->_filePath == "" ) {
        this->_filePath = path;
    } else {
        throw "FileWatcher already watching. Call to watch() not allowed";
    }
}

void FileWatcher::sl_fileChanged(QString path) {
    qDebug() << "Le fichier " << path << " a changé.";
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
    qDebug() << "Variable content émise: " << fileContent;
}
