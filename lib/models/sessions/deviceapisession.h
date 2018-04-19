#ifndef DEVICEAPISESSION_H
#define DEVICEAPISESSION_H

#include "apisession.h"

namespace Dsr {

class DeviceApiSession : public ApiSession {
public:
    explicit DeviceApiSession(QJsonDocument doc);
};

}

#endif // DEVICEAPISESSION_H
