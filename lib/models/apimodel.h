#ifndef APIMODEL_H
#define APIMODEL_H

#include <QObject>
#include <QJsonObject>
#include <QDateTime>

#define DEFAULT_VALUE_FOR_ID -1

namespace Dsr{

enum ModelDataSource { NotPersisted, Api, LocalDb };

class ApiModel {

protected:
    //  Api Fields
    int Id;

    QDateTime *createdAt = nullptr;
    QDateTime *updatedAt = nullptr;

    //  DataSource management
    Dsr::ModelDataSource dataSource;
    QDateTime *synced = nullptr;

    ApiModel(Dsr::ModelDataSource = NotPersisted);
    ApiModel(QJsonObject,Dsr::ModelDataSource = NotPersisted);

    virtual ~ApiModel();

    void UpdateAttributes(QJsonObject);

public:
    virtual bool Save(bool apiSave = true) = 0;
    virtual bool Delete(bool apiDelete = true) = 0;

    int GetId();

    QDateTime *GetCreatedAt();
    QDateTime *GetUpdatedAt();

    Dsr::ModelDataSource GetDataSource();

    QDateTime *GetSynced();

signals:
    void ApiModelSaveSuccess(ApiModel *aModel, bool apiSave);
    void ApiModelSaveFailure(ApiModel *aModel, bool apiSave);

public slots:
};

}

#endif // APIMODEL_H
