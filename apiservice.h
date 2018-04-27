#ifndef APISERVICE_H
#define APISERVICE_H

#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>

class ApiService : public QObject
{
    Q_OBJECT
public:
    ApiService();
    ~ApiService();
    void sendScores(QJsonObject game);
    void logout();
    void login(QString username, QString password);
    bool isConnected();
    QString getToken();
    void setToken(QString token);

signals:
    void loginComplete(QJsonObject);
    void gameSubmitted(QJsonObject);
    void errorOccured(QByteArray);

public slots:
    void sl_requestFinished(QNetworkReply*);

private:
    QUrl _generateFullUrl(QString endpoint);
    QString _baseUrl;
    QString _apiRoot;
    QString _token;
    QNetworkAccessManager *_networkManager;

    QString _authEndpoint;
    QString _gamesEndpoint;

    QJsonObject _resultToJsonObject(QByteArray json);
};

#endif // APISERVICE_H
