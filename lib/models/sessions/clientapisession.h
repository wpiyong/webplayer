#ifndef CLIENTAPISESSION_H
#define CLIENTAPISESSION_H

#include "apisession.h"

namespace Dsr {

class ClientApiSession : public ApiSession {

public:
    explicit ClientApiSession(QJsonDocument doc);

};

}

#endif // CLIENTAPISESSION_H
