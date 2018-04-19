#ifndef APISERVICES_H
#define APISERVICES_H

#include <QObject>
#include <QNetworkReply>
#include <QAuthenticator>

#include "models/revolutionset.h"
#include "models/revolution.h"
#include "models/sessions/apisession.h"
#include "models/sessions/clientapisession.h"
#include "models/sessions/userapisession.h"
#include "models/sessions/deviceapisession.h"

namespace Dsr {

enum RequestMethod {
    GET,
    POST,
    PUT,
    DELETE
};

struct DsrNetworkReply {
    int qtReplyCode;
    int httpReplyCode;
    QByteArray httpReplyData;
};

class ApiServices : public QObject {
    Q_OBJECT

private:

    QString clientId;
    QString clientSecret;
    QString token;
    QNetworkAccessManager networkMgr;
private:
    QVector<RevolutionSet*> revoSets;
public:
    static ApiServices* SharedInstance(QString aClientId, QString aClientSecret);
    void DownloadImage(QString);
    QString& getToken();
private:
    explicit ApiServices(QString aClientId = "", QString aClientSecret = "", QObject *parent = nullptr);
    QJsonDocument FetchAccessToken(QJsonObject Credentials);
    QJsonDocument SendPostRequest(QString Url, QJsonObject Payload, QJsonObject Headers);
    QJsonDocument SendGetRequest(QString Url, QJsonObject Headers);
    DsrNetworkReply SendRequest(const RequestMethod Method, QString Url, QJsonObject Payload, QJsonObject Headers, int expectedHttpReplyCode);
public:
    QVector<RevolutionSet*>& FetchRevolutionSets(QString token);

signals:
    void DownloadFinished(QNetworkReply*);
public slots:
    void downloadFinished(QNetworkReply* reply);

};

}

#endif // APISERVICES_H
