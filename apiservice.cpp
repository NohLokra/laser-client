#include "apiservice.h"

ApiService::ApiService()
#ifdef QT_DEBUG
    : QObject(), _baseUrl("http://laser-web.local/api/")
#else
    : QObject(), _baseUrl("https://www.laser-web.com/")
#endif
{
    this->_networkManager = new QNetworkAccessManager(this);

    connect(this->_networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(sl_requestFinished(QNetworkReply*)));
}

ApiService::~ApiService()
{

}

void ApiService::generateToken(QString user, QString password) {
    QUrl finalUrl(this->_baseUrl + QString("generateToken")); //On initialise la requête avec l'url qui génère les tokens
    QNetworkRequest request(finalUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QByteArray postDatas;
    postDatas.append("username=" + user + "&password=" + password);

    this->_networkManager->post(request, postDatas);
}

void ApiService::sl_requestFinished(QNetworkReply* r) {
    if ( r->error() ) emit this->responseReceived(QByteArray(r->errorString().toStdString().c_str()));
    else emit this->responseReceived(r->readAll());
}
