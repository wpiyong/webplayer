#include "revolutiondownloadtask.h"
#include <QException>
#include "../downloadmanager.h"

using namespace Dsr;

RevolutionDownloadTask::RevolutionDownloadTask(QVector<QString> aRevolution, int aIndex, QObject* parent) : revolution(aRevolution), count(0), index(aIndex), QObject(parent){
    downloadManager = DownloadManager::SharedInstance();

    connect(downloadManager, SIGNAL(DownloadSaveFinished()), this, SLOT(DownloadSaveFinished()));
}

void Dsr::RevolutionDownloadTask::run(){
    if(revolution.size() > 0) {
        for(int i = 0; i < revolution.size(); i++){
            downloadManager->downloadFile(revolution.at(i), QString::number(index));
        }
    } else {
        emit RevolutionDownloadFinished(this);
    }
}

void RevolutionDownloadTask::DownloadSaveFinished(){
    count++;
    if(count == revolution.size()) {
        emit RevolutionDownloadFinished(this);
    }
}
