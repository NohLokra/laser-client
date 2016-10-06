#ifndef APISERVICE_H
#define APISERVICE_H

#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class ApiService : public QObject
{
    Q_OBJECT
public:
    ApiService();
    ~ApiService();
    void generateToken(QString user, QString password);
    void submit(QString text);
    void logout(QString token);

signals:
    void responseReceived(QByteArray);

public slots:
    void sl_requestFinished(QNetworkReply*);

private:
    QUrl _generateFullUrl(QString action);
    QString _baseUrl;
    QNetworkAccessManager *_networkManager;
};

#endif // APISERVICE_H
