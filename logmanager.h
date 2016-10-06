#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <QTextEdit>
#include <QDateTime>

class LogManager
{
public:
    LogManager(QTextEdit* logWindow);
    ~LogManager();

public slots:
    void log(QString);
    void error(QString);
    void debug(QString);

private:
    QTextEdit* _logWindow;
};

#endif // LOGMANAGER_H
