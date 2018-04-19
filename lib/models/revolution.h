#ifndef REVOLUTION_H
#define REVOLUTION_H

//#include <QSqlDatabase>
#include <QJsonObject>

#include "apimodel.h"

namespace Dsr {

class Revolution : ApiModel {

public:
    //  Sam - new stuff
    explicit Revolution(Dsr::ModelDataSource = NotPersisted);
    Revolution(QJsonObject,Dsr::ModelDataSource = NotPersisted);

    ~Revolution();

    void UpdateAttributes(QJsonObject);

    // Setters
    void SetId(int);
    void SetRevolutionSetId(int);
    void SetUploadedAt(QString);
    void SetRevolutionCreatedAt(QString);

    // Getters
    int GetId() const;
    int GetRevolutionSetId() const;
    QString GetUploadedAt() const;
    QString GetRevolutionCreatedAt() const;

    // Other Methods
    bool Save(bool apiSave = true) override;
    bool Delete(bool apiDelete = true) override;

private:
    // Database
    //QSqlDatabase* db;

    // Table Fields
    int Id;
    int RevolutionSetId;
    QString UploadedAt;
    QString RevolutionCreatedAt;
};

}
#endif // REVOLUTION_H
