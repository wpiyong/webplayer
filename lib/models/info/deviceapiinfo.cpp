#include "deviceapiinfo.h"

#include <QJsonDocument>
#include <QJsonObject>

/*****************************************
 * Constructor
*****************************************/
Dsr::DeviceApiInfo::DeviceApiInfo(QJsonDocument doc) : Dsr::ApiInfo(doc) {
    QJsonObject remote_host_doc = doc.object().value("device").toObject();
    this->id = remote_host_doc.value("Id").toInt();
    this->name = remote_host_doc.value("Name").toString();
    this->type = remote_host_doc.value("type").toString();
    this->updated = remote_host_doc.value("updated").toString();
    this->created = remote_host_doc.value("created").toString();
}

/*****************************************
 * Getters
*****************************************/
int Dsr::DeviceApiInfo::GetId(){
    return this->id;
}

QString Dsr::DeviceApiInfo::GetName(){
    return this->name;
}

QString Dsr::DeviceApiInfo::GetType(){
    return this->type;
}

QString Dsr::DeviceApiInfo::GetUpdated(){
    return this->GetUpdated();
}

QString Dsr::DeviceApiInfo::GetCreated(){
    return this->GetCreated();
}

