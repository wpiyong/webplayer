#include "apiservices.h"

#include <QJsonObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QProcess>
#include <QJsonParseError>
#include <QJsonArray>
#include <QVector>
#include <QSslConfiguration>

#include "./emprintf.h"

#ifndef NULL
#define NULL (0)
#endif

using namespace Dsr;

static ApiServices *_instance = NULL;
ApiServices* ApiServices::SharedInstance(QString aClientId, QString aClientSecret){
    if(_instance == NULL){
        _instance = new ApiServices(aClientId, aClientSecret);
    }

    return _instance;
}

ApiServices::ApiServices(QString aClientId, QString aClientSecret, QObject *parent) : QObject(parent), clientId(aClientId), clientSecret(aClientSecret) {
    // Get Access Token
    QJsonObject assCred;
    assCred.insert("grant_type", "password");
    // NOTE: this username should be changed for different user since different user has differenet clientid and secret
    assCred.insert("username", "yong-dsr-webm");
    assCred.insert("password", "password");
    //QJsonDocument assAccessTokenDoc = FetchAccessToken(assCred);

    //token = QString(assAccessTokenDoc.object().value("access_token").toString());

    QObject::connect(&networkMgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));
}

void ApiServices::DownloadImage(QString url) {

    QNetworkRequest request(url);
    networkMgr.get(request);

}

void ApiServices::downloadFinished(QNetworkReply *reply){
    ::emprintf("ApiServices::downloadFinished");
    emit DownloadFinished(reply);
}

QJsonDocument ApiServices::FetchAccessToken(QJsonObject Credentials){
    QString url;
    QJsonObject payload;
    QJsonObject headers;

    QString apiHost = "192.168.24.109:3000"; //"192.168.24.112:3000"; // development calven
    QString apiScheme = "http";

    // Set url
    url = QString("%1://%2/oauth2/token").arg(apiScheme, apiHost);

    // Set payload
    payload.insert("client_id", this->clientId);
    payload.insert("client_secret", this->clientSecret);
    if(Credentials.value("grant_type") == QJsonValue::Undefined){
        payload.insert("grant_type", "client_credentials");
    }
    else{
        payload.insert("grant_type", Credentials["grant_type"]);
        if(Credentials["grant_type"] == "password"){
            payload.insert("username", Credentials["username"]);
            payload.insert("password", Credentials["password"]);
        }
        if(Credentials["grant_type"] == "assertion"){
            payload.insert("assertion", Credentials["assertion"]);
        }
    }

    // Set headers
    headers.insert("Accept", "application/json");
    headers.insert("Content-Type", "application/json");
    //headers.insert("Access-Control-Allow-Origin", "*");

    // Send request
    QJsonDocument response = SendPostRequest(url, payload, headers);

    return response;
}

QJsonDocument ApiServices::SendPostRequest(QString Url, QJsonObject Payload, QJsonObject Headers){
    QJsonDocument json_result;

    // Send request
    int retryCount = 0;
    DsrNetworkReply reply;
    do{
        reply = SendRequest(POST, Url, Payload, Headers, 201);
        retryCount++;
    }while(reply.qtReplyCode == QNetworkReply::TimeoutError && retryCount < 3);

    QJsonParseError err;
    json_result = QJsonDocument::fromJson(reply.httpReplyData, &err);

    return json_result;
}

QJsonDocument ApiServices::SendGetRequest(QString Url, QJsonObject Headers){
    QJsonDocument json_result;
    QJsonObject Payload;

    // Send request
    int retryCount = 0;
    Dsr::DsrNetworkReply reply;
    do{
        reply = SendRequest(GET, Url, Payload, Headers, 200);
        retryCount++;
    }while(reply.qtReplyCode == QNetworkReply::TimeoutError && retryCount < 3);

    QJsonParseError err;
    json_result = QJsonDocument::fromJson(reply.httpReplyData, &err);

    return json_result;
}

DsrNetworkReply ApiServices::SendRequest(const RequestMethod Method, QString Url, QJsonObject Payload, QJsonObject Headers, int expectedHttpReplyCode){
    QNetworkRequest req;
    QNetworkReply* reply;
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;

    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    // Set request header
    foreach(const QJsonValue &key, Headers.keys()) {
        req.setRawHeader(QByteArray(key.toString().toUtf8()), QByteArray(Headers[key.toString()].toString().toUtf8()));
    }

    // Set request url
    QUrl realUrl(Url);
    req.setUrl(realUrl);
    QByteArray jsonString = "{\"client_id\": \"2bb931d856205a2dd781258bb224a31195fe735200635f03a7f58f9d2e094023\", \"client_secret\": \"5971e6c681ca791473607d3b66cabffd3fc6504587698cb11fd16604d4a44a6e\", \"grant_type\": \"password\", \"password\": \"password\", \"username\": \"yong-dsr-webm\" }";
    // Set to ignore ssl errors
    //QSslConfiguration sslConfig = req.sslConfiguration();
    //sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
    //req.setSslConfiguration(sslConfig);

    // Send out request based on method
    switch(Method) {
        case GET:
            reply = mgr.get(req);
            break;
        case POST:
            reply = mgr.post(req, QJsonDocument(Payload).toJson());
            //reply = mgr.post(req, jsonString);
            break;
        case PUT:
            reply = mgr.put(req, QJsonDocument(Payload).toJson());
            break;
        case DELETE:
            break;
    }
    eventLoop.exec();

    DsrNetworkReply dsrReply;

    // Extract code
    dsrReply.qtReplyCode = reply->error();
    dsrReply.httpReplyCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    // Extract data
    if(reply->error() == QNetworkReply::NoError && dsrReply.httpReplyCode == expectedHttpReplyCode){
        dsrReply.httpReplyData = reply->readAll();
    }
    else{
        //qDebug() << "SendRequest failed!";
    }

    // Free reply
    delete reply;

    // Return dsr reply
    return dsrReply;
}

QVector<RevolutionSet*>& ApiServices::FetchRevolutionSets(QString token){
    QString url;
    QJsonObject payload;
    QJsonObject headers;

    QString apiHost = "192.168.24.109:3000"; // development
    QString apiScheme = "http";

    // Setup url
    url = QString("%1://%2/api/v2/revolution_sets.json").arg(apiScheme, apiHost);

    // Setup headers
    headers.insert("Accept", "application/json");
    headers.insert("Content-Type", "application/json");
    headers.insert("Authorization", QString("Bearer %1").arg(token));
    //headers.insert("Access-Control-Allow-Origin", "*");

    // Send request
    QJsonDocument response = SendGetRequest(url, headers);
    QJsonObject rootObject = response.object();

    //QVector<RevolutionSet*> revSets;
    revoSets.clear();
    if(rootObject.contains("revolution_sets") && rootObject.value("revolution_sets").isArray()){
        QJsonArray jsonArr = rootObject.value("revolution_sets").toArray();
        foreach (const QJsonValue & value, jsonArr) {
            revoSets.push_back(new RevolutionSet(value.toObject()));
        }
    }

    return revoSets;
}

QString& ApiServices::getToken(){
    return token;
}
