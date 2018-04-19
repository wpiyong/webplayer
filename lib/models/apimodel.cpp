#include "apimodel.h"
#include <QJsonValue>

Dsr::ApiModel::ApiModel(Dsr::ModelDataSource aDataSource) : Id(DEFAULT_VALUE_FOR_ID), dataSource(aDataSource) {

}

Dsr::ApiModel::ApiModel(QJsonObject jsonObj, Dsr::ModelDataSource aDataSource) : dataSource(aDataSource) {

}

Dsr::ApiModel::~ApiModel(){

}

void Dsr::ApiModel::UpdateAttributes(QJsonObject jsonObj){
    if(jsonObj.contains("id")){
        this->Id = jsonObj.value("id").toInt();
    }

    if(jsonObj.contains("updated_at")){
//        this->updatedAt = jsonObj.value("updated_at").toString();
    }

    if(jsonObj.contains("created_at")){
//        this->createdAt = jsonObj.value("created_at").toString();
    }

    this->synced = new QDateTime(QDateTime::currentDateTime());
}

int Dsr::ApiModel::GetId(){
    return this->Id;
}

QDateTime* Dsr::ApiModel::GetCreatedAt(){
    return this->createdAt;
}
QDateTime* Dsr::ApiModel::GetUpdatedAt(){
    return this->updatedAt;
}

Dsr::ModelDataSource Dsr::ApiModel::GetDataSource(){
    return this->dataSource;
}

QDateTime* Dsr::ApiModel::GetSynced(){
    return this->synced;
}
