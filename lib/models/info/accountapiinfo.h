#ifndef ACCOUNTAPIINFO_H
#define ACCOUNTAPIINFO_H

#include "apiinfo.h"

namespace Dsr {

class AccountApiInfo : public ApiInfo {

public:
    explicit AccountApiInfo(QJsonDocument doc);

    // Getters
    int GetId();
    QString GetName();
    QString GetDescription();
    QString GetBannerImage();
    QString GetTermsAndConditions();

private:
    int id;
    QString name;
    QString description;
    QString bannerImage;
    QString termsAndConditions;

};

}

#endif // ACCOUNTAPIINFO_H
