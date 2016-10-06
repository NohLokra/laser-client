#include "logmanager.h"

LogManager::LogManager(QTextEdit *logWindow) : _logWindow(logWindow)
{

}

LogManager::~LogManager()
{

}

void LogManager::log(QString str) {
    QDateTime now();
    QString msg = "[LOG] " + now.toString("HH:mm:ss") + " " + str;

    this->_logWindow->append(msg);
}

void LogManager::debug(QString str) {
    QDateTime now();
    QString msg = "[DEBUG] " + now.toString("HH:mm:ss") + " " + str;

    this->_logWindow->append(msg);
}

void LogManager::error(QString str) {
    QDateTime now();
    QString msg = "[ERROR] " + now.toString("HH:mm:ss") + " " + str;

    this->_logWindow->append(msg);
}
