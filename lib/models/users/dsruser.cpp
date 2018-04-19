#include "dsruser.h"

Dsr::DsrUser::DsrUser(Dsr::ModelDataSource aDataSource) : ApiModel(aDataSource) {

}

Dsr::DsrUser::DsrUser(QJsonObject jsonObj,Dsr::ModelDataSource aDataSource) : ApiModel(jsonObj, aDataSource) {
    this->UpdateAttributes(jsonObj);
}

void Dsr::DsrUser::UpdateAttributes(QJsonObject jsonObj){
    Dsr::ApiModel::UpdateAttributes(jsonObj);
}
