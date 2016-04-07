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

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:

public slots:
    void setViewOnCredentials();
    void setViewOnHome();

private:
    QMenuBar* _menu;
    QMenu* _menuNavigation;
    QAction* _actionHome;
    QAction* _actionCredentials;

    QWidget* _authWidget;
    QFormLayout* _authLayout;
    QLineEdit* _login;
    QLineEdit* _password;
    QPushButton* _connection;

    QWidget* _homeWidget;
    QVBoxLayout* _mainLayout;
    QPushButton* _startStop;
    QTextEdit* _logs;

    QStackedWidget* _mainWidget;
};

#endif // MAINWINDOW_H
