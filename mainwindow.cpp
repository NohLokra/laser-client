#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), _page(Home)
{

    //Navigation
    _mainWidget = new QStackedWidget();

    //Panneau d'authentification
    _authWidget = new QWidget();
    _authLayout = new QFormLayout();

    _login = new QLineEdit();
    _authLayout->addRow("Identifiant", _login);

    _password = new QLineEdit();
    _authLayout->addRow("Mot-de-passe", _password);

    _connection = new QPushButton("Connexion");
    _authLayout->addRow(_connection);

    _loginOutput = new QLabel();
    _authLayout->addRow(_loginOutput);

    _authWidget->setLayout(_authLayout);

    connect(_connection, SIGNAL(clicked()), this, SLOT(sl_buttonLoginClicked()));

    //Page d'accueil
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

    //Ajout des panneaux au widget principal
    _mainWidget->addWidget(_homeWidget);
    _mainWidget->addWidget(_authWidget);

    this->setCentralWidget(_mainWidget);

    //Menu
    _menu = new QMenuBar();
    _menuNavigation = new QMenu("Menu");
    _actionHome = _menuNavigation->addAction("Accueil");
    _actionCredentials = _menuNavigation->addAction("Connexion");

    _menu->addMenu(_menuNavigation);
    this->setMenuBar(_menu);

    this->setFixedSize(320, 180);

    connect(_actionCredentials, SIGNAL(triggered()), this, SLOT(setViewOnCredentials()));
    connect(_actionHome, SIGNAL(triggered()), this, SLOT(setViewOnHome()));

    //WebService
    _api = new ApiService();
    connect(_api, SIGNAL(loginComplete(QJsonObject)), this, SLOT(sl_loginComplete(QJsonObject)));
    connect(_api, SIGNAL(gameSubmitted(QJsonObject)), this, SLOT(sl_gameSubmitted(QJsonObject)));

    _logManager = new LogManager(_logs);
}

MainWindow::~MainWindow()
{

}

void MainWindow::setViewOnCredentials()
{
    _page = Auth;
    this->_mainWidget->setCurrentIndex(1);
}

void MainWindow::setViewOnHome()
{
    _page = Home;
    this->_mainWidget->setCurrentIndex(0);
}

Page MainWindow::getCurrentView() {
    return _page;
}

int MainWindow::getCurrentViewIndex() {
    return (int)_page;
}

void MainWindow::setView(Page p) {
    switch(p) {
    case Home:
        setViewOnHome();
        break;
    case Auth:
        setViewOnCredentials();
        break;

    default:
        setViewOnHome();
        break;
    }
}

void MainWindow::sl_buttonLoginClicked() {
    QString username = _login->text();
    QString password = _password->text();

    _api->login(username, password);
}

void MainWindow::sl_loginComplete(QJsonObject response) {
    qDebug() << "Réponse du login" << response;

    _api->setToken(response.value("token").toString());

    setLoginSuccess(tr("Vous êtes connecté !"));
    watchLaserFile();
}

void MainWindow::sl_gameSubmitted(QJsonObject game) {
    qDebug() << "Réponse de l'envoi de partie" << game;

    _logManager->log("Contenu du fichier envoyé à la base de données");
}

void MainWindow::setLoginError(QString s) {
    _loginOutput->setText("<span style='color: red'>Erreur: " + s + "</span>");
}

void MainWindow::setLoginSuccess(QString s) {
    _loginOutput->setText("<span style='color: green'>" + s + "</span>");
}

void MainWindow::watchLaserFile() {
#ifdef QT_DEBUG
    QString path = "./LQM_COM_FILE.TXT";
#else
    QString path = "C:/"; //TODO locate(LQM_COM_FILE.TXT)
#endif
    FileWatcher *fw = new FileWatcher();
    fw->watch(path);

    qDebug() << "Surveillance du fichier des scores en place";

    connect(fw, SIGNAL(fileContentChanged(QString)), this, SLOT(sl_fileContentChanged(QString)));
}

void MainWindow::sl_fileContentChanged(QString content) {
    ScoreParser sp(content);

    qDebug() << QJsonDocument(sp.jsonParse()).toJson(QJsonDocument::Indented);

    _api->sendScores(sp.jsonParse());

    qDebug() << "API Appelée";
}
