#include "accountapiinfo.h"

#include <QJsonDocument>
#include <QJsonObject>

/*****************************************
 * Constructor
*****************************************/
Dsr::AccountApiInfo::AccountApiInfo(QJsonDocument doc) : Dsr::ApiInfo(doc) {
    QJsonObject accInfo = doc.object().value("device").toObject().value("Account").toObject();
    this->id = accInfo.value("id").toInt();
    this->name = accInfo.value("Name").toString();
    this->description = accInfo.value("Description").toString();
    this->bannerImage = accInfo.value("BannerImage").toString();
    this->termsAndConditions = accInfo.value("TermsAndConditions").toString();
}

/*****************************************
 * Getters
*****************************************/
int Dsr::AccountApiInfo::GetId(){
    return this->id;
}

QString Dsr::AccountApiInfo::GetName(){
    return this->name;
}

QString Dsr::AccountApiInfo::GetDescription(){
    return this->description;
}

QString Dsr::AccountApiInfo::GetBannerImage(){
    return this->bannerImage;
}

QString Dsr::AccountApiInfo::GetTermsAndConditions(){
    return this->termsAndConditions;
}
