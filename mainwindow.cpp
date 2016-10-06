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

    connect(_connection, SIGNAL(clicked()), this, SLOT(sl_getToken()));

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
    connect(_api, SIGNAL(responseReceived(QByteArray)), this, SLOT(handleApiResponse(QByteArray)));
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

void MainWindow::setViewIndex(int index) {
    Page p = Page(index);
    setView(p);
}

void MainWindow::sl_getToken() {
    QString username = _login->text();
    QString password = _password->text();

    _api->generateToken(username, password);
}

void MainWindow::handleApiResponse(QByteArray response) {
    qDebug() << response;

    QJsonDocument document = QJsonDocument::fromJson(response);
    QJsonObject object = document.object();

    bool success = object.value("success").toBool(false);
    QString action = object.value("action").toString();

    if ( action == "login" ) {
        if ( !success ) {
            _logged = false;
            _setLoginError(object.value("error").toString());
        } else {
            _logged = true;
            _token = object.value("token").toString();
            _setLoginSuccess(tr("Connexion effectuée avec succès."));
            this->watchLaserFile();
        }
    } else if ( action == "logout" ) {
        if ( !success ) {
            _setLoginError(tr("Impossible de vous déconnecter"));
        } else {
            _setLoginSuccess(tr("Vous avez été déconnecté avec succès."));
            _logged = false;
            _token = "";
        }
    } else if ( action == "submit" ) {
        if ( !success ) {

        } else {

        }
    }
}

void MainWindow::_setLoginError(QString s) {
    _loginOutput->setText("<span style='color: red'>Erreur: " + s + "</span>");
}

void MainWindow::_setLoginSuccess(QString s) {
    _loginOutput->setText("<span style='color: green'>" + s + "</span>");
}

void MainWindow::watchLaserFile() {
#ifdef QT_DEBUG
    QString path = "C:/Users/Zozo/Programmation/C++/Qt/laser-client/test.txt";
#else
    QString path = "C:/"; //TODO
#endif
    FileWatcher *fw = new FileWatcher(path);
    connect(fw, SIGNAL(fileContentChanged(QString)), this, SLOT(sl_fileContentCanged(QString)));
    qDebug() << "Watching laser file";
}

void MainWindow::sl_fileContentCanged(QString content) {
    qDebug() << "New content: " << content;
    _logManager->log("Contenu du fichier envoyé à la base de données");
    this->_api->submit(content, _token);
}
