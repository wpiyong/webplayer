#ifndef DSRUSER_H
#define DSRUSER_H

#include <QJsonObject>

#include "../apimodel.h"

namespace Dsr{

class DsrUser : public ApiModel {
public:
    DsrUser(Dsr::ModelDataSource = NotPersisted);
    DsrUser(QJsonObject,Dsr::ModelDataSource = NotPersisted);

    void UpdateAttributes(QJsonObject);
};

}


#endif // DSRUSER_H
