#include "revolution.h"

//#include <QSqlQuery>
//#include <QSqlError>
#include <QDebug>

Dsr::Revolution::Revolution(Dsr::ModelDataSource aDataSrc) : ApiModel(aDataSrc), Id(DEFAULT_VALUE_FOR_ID) {

}

Dsr::Revolution::Revolution(QJsonObject jsonObj,Dsr::ModelDataSource aDataSrc) : ApiModel(jsonObj, aDataSrc) {
    this->UpdateAttributes(jsonObj);
}

Dsr::Revolution::~Revolution(){

}

void Dsr::Revolution::UpdateAttributes(QJsonObject jsonObj) {
    Dsr::ApiModel::UpdateAttributes(jsonObj);

    qDebug() << "Revolution Set Update Attributes!!!!";
}

// Setters
void Dsr::Revolution::SetId(int Id) {
    this->Id = Id;
}

void Dsr::Revolution::SetRevolutionSetId(int Id) {
    this->RevolutionSetId = Id;
}

void Dsr::Revolution::SetUploadedAt(QString Date) {
    this->UploadedAt = Date;
}

void Dsr::Revolution::SetRevolutionCreatedAt(QString RevoNum) {
    this->RevolutionCreatedAt = RevoNum;
}

// Getters
int Dsr::Revolution::GetId() const {
    return this->Id;
}

int Dsr::Revolution::GetRevolutionSetId() const {
    return this->RevolutionSetId;
}

QString Dsr::Revolution::GetUploadedAt() const {
    return this->UploadedAt;
}

QString Dsr::Revolution::GetRevolutionCreatedAt() const {
    return this->RevolutionCreatedAt;
}

// Other Methods
bool Dsr::Revolution::Save(bool apiSave){

    return true;
}

bool Dsr::Revolution::Delete(bool apiDelete){

    return true;
}
