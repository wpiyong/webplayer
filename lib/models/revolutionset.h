#ifndef REVOLUTIONSET_H
#define REVOLUTIONSET_H

//#include <QSqlDatabase>
#include <QVector>
#include <QJsonObject>
#include <QMap>

#include "apimodel.h"
#include "revolution.h"
#include "./users/dsrenduser.h"
#include "./camera_systems/camerasystem.h"

namespace Dsr {

class RevolutionSet : ApiModel {

public:
    //  Sam - new stuff
    explicit RevolutionSet(Dsr::ModelDataSource = NotPersisted);
    RevolutionSet(QJsonObject,Dsr::ModelDataSource = NotPersisted);

    ~RevolutionSet();

    // Setters
    void SetId(int Id);
    void SetEmail(QString Email);
    void SetMetaDataString(QString metaDataString);
    void SetPrintLayout(QString printLayout);
    void SetPrintNumberOfCopies(int printNumberOfCopies);
    void SetUploadedAt(QString Datetime);
    void SetRevolutionSetCreatedAt(QString Datetime);
    void SetSerial(QString serial);

    void AddRevolution(Revolution* Revo);

    // Getters
    int GetId() const;
    QString GetEmail() const;
    QString GetUploadedAt() const;
    QString GetMetaDataString() const;
    QString GetPrintLayout() const;
    int GetPrintNumberOfCopies() const;
    QString GetRevolutionSetCreatedAt() const;
    QVector<Revolution*> GetRevolutions() const;
    QString GetSerial() const;

    // Other Methods
    bool Save(bool apiSave = true) override;
    bool Delete(bool apiDelete = true) override;

    // Static methods
    static QVector<RevolutionSet*>* GetUnuploadedRevoSets();

private:
    // Database
    //QSqlDatabase* db;

    // Table Fields
    int Id;
    QString Email;
    QString MetaDataString;
    QString PrintLayout;
    int PrintNumberOfCopies;
    QString UploadedAt;
    QString RevolutionSetCreatedAt;

    // Revolutions
    QVector<Revolution*> Revos;

    //  Sam - Api Attributes
    void UpdateAttributes(QJsonObject);
    void ClearRevos();

    //  CTRL [Api Only] Fields
    QString Serial;
    QMap<QString,QString> metaData;

    DsrEndUser *createdBy;
    CameraSystem *createdOn;

};

}
#endif // REVOLUTIONSET_H
