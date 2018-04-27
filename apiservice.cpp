#include "apiservice.h"

ApiService::ApiService()
#ifdef QT_DEBUG
    : QObject(), _baseUrl("http://localhost:9000"), _apiRoot("/api"), _token(""), _authEndpoint("/auth/center"), _gamesEndpoint("/games")
#else
    : QObject(), _baseUrl("https://www.laser-web.com/api/"), _token(), _authEndpoint("auth/center"), _gamesEndpoint("games")
#endif
{
    this->_networkManager = new QNetworkAccessManager(this);
    connect(this->_networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(sl_requestFinished(QNetworkReply*)));
}

ApiService::~ApiService()
{

}

void ApiService::sendScores(QJsonObject game) {
    if ( !isConnected() ) {
        return;
    }

    QUrl finalUrl = this->_generateFullUrl(_gamesEndpoint);
    QNetworkRequest request(finalUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    qDebug() << "Envoi des scores à " << finalUrl.toString();

    game.insert("access_token", _token);

    QByteArray postData = QJsonDocument(game).toJson(QJsonDocument::Compact);

    this->_networkManager->post(request, postData);
}

void ApiService::login(QString username, QString password) {
    QUrl url = _generateFullUrl(_authEndpoint);

    QString authorization(username + ":" + password);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Authorization", "Basic " + authorization.toUtf8().toBase64());

    QByteArray postData;

    this->_networkManager->post(request, postData);
}

void ApiService::logout() {
    _token = "";
}

bool ApiService::isConnected() {
    return _token != "";
}

QString ApiService::getToken() {
    return _token;
}

void ApiService::sl_requestFinished(QNetworkReply* r) {
    QUrl url = r->url();
    QString path = url.path();

    qDebug() << "Réponse de " << path;
    if ( r->error() ) {
      emit errorOccured(QByteArray(r->errorString().toStdString().c_str()));
    } else {
        QJsonDocument doc = QJsonDocument::fromJson(r->readAll());
        QJsonObject object = doc.object();

        if ( path == _apiRoot + _authEndpoint ) {
            emit loginComplete(object);
        } else if ( path == _apiRoot + _gamesEndpoint ) {
            emit gameSubmitted(object);
        }
    }
}

QUrl ApiService::_generateFullUrl(QString endpoint) {
    return this->_baseUrl + _apiRoot + endpoint;
}

void ApiService::setToken(QString token) {
    _token = token;
}
