#ifndef DEVICEAPIINFO_H
#define DEVICEAPIINFO_H

#include "apiinfo.h"

namespace Dsr {

class DeviceApiInfo : public ApiInfo {

public:
    explicit DeviceApiInfo(QJsonDocument doc);

    // Getters
    int GetId();
    QString GetName();
    QString GetType();
    QString GetAccount();
    QString GetUpdated();
    QString GetCreated();

private:
    int id;
    QString name;
    QString type;
    QString updated;
    QString created;
};

}

#endif // DEVICEAPIINFO_H
