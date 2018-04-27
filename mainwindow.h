#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMenuBar>
#include <QStackedWidget>
#include <QJsonValue>

#include "apiservice.h"
#include "filewatcher.h"
#include "mainwindow.h"
#include "logmanager.h"
#include "scoreparser.h"

enum Page {
    Home = 0,
    Auth = 1
};

typedef enum Page Page;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Page getCurrentView();
    int getCurrentViewIndex();
    void setView(Page);
    void watchLaserFile();
    void setLoginError(QString s);
    void setLoginSuccess(QString s);

signals:

public slots:
    void setViewOnCredentials();
    void setViewOnHome();

    void sl_buttonLoginClicked();
    void sl_fileContentChanged(QString content);
    void sl_loginComplete(QJsonObject);
    void sl_gameSubmitted(QJsonObject);

private:
    //Navigation
    QStackedWidget* _mainWidget;
    Page _page;

    //Widgets du menu
    QMenuBar* _menu;
    QMenu* _menuNavigation;
    QAction* _actionHome;
    QAction* _actionCredentials;

    //Widgets pour le panneau d'authentification
    QWidget* _authWidget;
    QFormLayout* _authLayout;
    QLineEdit* _login;
    QLineEdit* _password;
    QPushButton* _connection;
    QLabel* _loginOutput;

    //Widget pour le panneau d'accueil
    QWidget* _homeWidget;
    QVBoxLayout* _mainLayout;
    QPushButton* _startStop;
    QTextEdit* _logs;

    //Partie WebService
    ApiService *_api;
    LogManager* _logManager;

};

#endif // MAINWINDOW_H
