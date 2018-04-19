#ifndef APISESSION_H
#define APISESSION_H

#include <QJsonDocument>

namespace Dsr {

class ApiSession{

public:
    explicit ApiSession(QJsonDocument doc);

    // Getters
    int GetCreatedAt();
    QString GetTokenType();
    QString GetAccessToken();
    int GetExpiresIn();

protected:
    int CreatedAt;
    QString TokenType;
    QString AccessToken;
    int ExpiresIn;

};

}

#endif // APISESSION_H
