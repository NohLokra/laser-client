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

signals:
    void responseReceived(QByteArray);

public slots:
    void sl_requestFinished(QNetworkReply*);

private:
    QString _baseUrl;
    QNetworkAccessManager *_networkManager;
};

#endif // APISERVICE_H
