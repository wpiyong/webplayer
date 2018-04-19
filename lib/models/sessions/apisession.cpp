#include "apisession.h"

#include <QJsonDocument>
#include <QJsonObject>

/*****************************************
 * Constructor
*****************************************/
Dsr::ApiSession::ApiSession(QJsonDocument doc){
    this->CreatedAt = doc.object().value("created_at").toInt();
    this->TokenType = doc.object().value("token_type").toString();
    this->AccessToken = doc.object().value("access_token").toString();
    this->ExpiresIn = doc.object().value("expires_in").toInt();
}

/*****************************************
 * Getters
*****************************************/
int Dsr::ApiSession::GetCreatedAt() {
    return this->CreatedAt;
}

QString Dsr::ApiSession::GetTokenType() {
    return this->TokenType;
}

QString Dsr::ApiSession::GetAccessToken() {
    return this->AccessToken;
}

int Dsr::ApiSession::GetExpiresIn() {
    return this->ExpiresIn;
}
