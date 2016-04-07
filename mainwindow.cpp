#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    _mainWidget = new QStackedWidget();

    _authWidget = new QWidget();
    _authLayout = new QFormLayout();

    _login = new QLineEdit();
    _authLayout->addRow("Identifiant", _login);

    _password = new QLineEdit();
    _authLayout->addRow("Mot-de-passe", _password);

    _connection = new QPushButton("Connexion");
    _authLayout->addRow(_connection);

    _authWidget->setLayout(_authLayout);

    _homeWidget = new QWidget();
    _mainLayout = new QVBoxLayout();

    _logs = new QTextEdit();
    _logs->setPalette(QPalette(Qt::black));
    _logs->setTextColor(Qt::white);
    _logs->setReadOnly(true);
    _mainLayout->addWidget(_logs);

    _startStop = new QPushButton("Démarrer");
    _startStop->setCheckable(true);
    _mainLayout->addWidget(_startStop);

    _homeWidget->setLayout(_mainLayout);

    _mainWidget->addWidget(_homeWidget);
    _mainWidget->addWidget(_authWidget);

    this->setCentralWidget(_mainWidget);

    _menu = new QMenuBar();
    _menuNavigation = new QMenu("Connexion");
    _actionHome = _menuNavigation->addAction("Accueil...");
    _actionCredentials = _menuNavigation->addAction("Identifiants...");

    _menu->addMenu(_menuNavigation);
    this->setMenuBar(_menu);

    this->setFixedSize(320, 180);

    connect(_actionCredentials, SIGNAL(triggered()), this, SLOT(setViewOnCredentials()));
    connect(_actionHome, SIGNAL(triggered()), this, SLOT(setViewOnHome()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::setViewOnCredentials()
{
    this->_mainWidget->setCurrentIndex(1);
}

void MainWindow::setViewOnHome()
{
    this->_mainWidget->setCurrentIndex(0);
}
