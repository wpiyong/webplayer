#ifndef USERAPISESSION_H
#define USERAPISESSION_H

#include "apisession.h"

namespace Dsr {

class UserApiSession : public ApiSession {
public:
    explicit UserApiSession(QJsonDocument doc);
};

}

#endif // USERAPISESSION_H
