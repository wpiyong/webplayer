#include "revolutionset.h"

//#include <QSqlQuery>
//#include <QSqlError>
#include <QDebug>
#include <QJsonArray>

#include "revolution.h"

Dsr::RevolutionSet::RevolutionSet(Dsr::ModelDataSource aDataSrc) : ApiModel(aDataSrc), Id(DEFAULT_VALUE_FOR_ID), createdBy(nullptr), createdOn(nullptr) {
    this->Revos = QVector<Revolution*>(0);
}

Dsr::RevolutionSet::RevolutionSet(QJsonObject jsonObj,Dsr::ModelDataSource aDataSrc) : ApiModel(jsonObj, aDataSrc) {
    this->Revos = QVector<Revolution*>(0);
    qDebug() << "before starting the whole business, the vector is " << (this->Revos.isEmpty() ? "EMPTY" : "NOT EMPTY!");
    this->UpdateAttributes(jsonObj);
}

void Dsr::RevolutionSet::UpdateAttributes(QJsonObject jsonObj) {
    Dsr::ApiModel::UpdateAttributes(jsonObj);

    qDebug() << "Revolution Set Update Attributes!!!!";
    if(jsonObj.contains("Serial")){
        this->Serial = jsonObj.value("Serial").toString();
    }

    this->ClearRevos();
    if(jsonObj.contains("Revolutions") && jsonObj.value("Revolutions").isArray()){
        QJsonArray revsJson = jsonObj.value("Revolutions").toArray();
        for(int i = 0 ; i < revsJson.count() ; i++ ){
            QJsonObject jsonObj = revsJson[i].toObject();
            this->Revos.push_back(new Dsr::Revolution(jsonObj, this->dataSource));
        }
    }
}

Dsr::RevolutionSet::~RevolutionSet(){
    //  Destruct this class' attributes

    if(this->createdBy != nullptr){
        delete this->createdBy;
    }

    if(this->createdOn != nullptr){
        delete this->createdOn;
    }

    this->ClearRevos();
}

// QQQ TODO INCOMPLETE METHOD! DO NOT USE
void Dsr::RevolutionSet::ClearRevos(){

}

// Setters
void Dsr::RevolutionSet::SetId(int Id){
    this->Id = Id;
}

void Dsr::RevolutionSet::SetEmail(QString Email){
    this->Email = Email;
}

void Dsr::RevolutionSet::SetMetaDataString(QString metaDataString){
    this->MetaDataString = metaDataString;
}

void Dsr::RevolutionSet::SetPrintLayout(QString printLayout){
    this->PrintLayout = printLayout;
}

void Dsr::RevolutionSet::SetPrintNumberOfCopies(int printNumberOfCopies){
    this->PrintNumberOfCopies = printNumberOfCopies;
}

void Dsr::RevolutionSet::SetUploadedAt(QString Datetime){
    this->UploadedAt = Datetime;
}

void Dsr::RevolutionSet::SetRevolutionSetCreatedAt(QString Datetime){
    this->RevolutionSetCreatedAt = Datetime;
}

void Dsr::RevolutionSet::SetSerial(QString serial){
    this->Serial = serial;
}

void Dsr::RevolutionSet::AddRevolution(Revolution* Revo){
    this->Revos.push_back(Revo);
}

// Getters
int Dsr::RevolutionSet::GetId() const{
    return this->Id;
}

QString Dsr::RevolutionSet::GetEmail() const{
    return this->Email;
}

QString Dsr::RevolutionSet::GetMetaDataString() const {
    return this->MetaDataString;
}

QString Dsr::RevolutionSet::GetPrintLayout() const {
    return this->PrintLayout;
}

int Dsr::RevolutionSet::GetPrintNumberOfCopies() const {
    return this->PrintNumberOfCopies;
}

QString Dsr::RevolutionSet::GetUploadedAt() const{
    return this->UploadedAt;
}

QString Dsr::RevolutionSet::GetRevolutionSetCreatedAt() const{
    return this->RevolutionSetCreatedAt;
}

QVector<Dsr::Revolution*> Dsr::RevolutionSet::GetRevolutions() const{
    return this->Revos;
}

QString Dsr::RevolutionSet::GetSerial() const{
    return this->Serial;
}

// Other Methods
bool Dsr::RevolutionSet::Save(bool apiSave){

    return true;
}

bool Dsr::RevolutionSet::Delete(bool apiDelete){

    return true;
}

// Static Method
QVector<Dsr::RevolutionSet*>* Dsr::RevolutionSet::GetUnuploadedRevoSets() {
    QVector<RevolutionSet*>* sets = new QVector<RevolutionSet*>;

    return sets;
}
