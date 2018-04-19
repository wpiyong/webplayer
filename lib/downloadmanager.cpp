#include "downloadmanager.h"
#include <QFile>
#include <QDir>

using namespace Dsr;

/*****************************************
 * Constructor
*****************************************/
DownloadManager::DownloadManager(QObject *parent) : QObject(parent) {
    // Connect download finish signal from network access manager
    connect(&this->netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));
}


/*****************************************
 * Singleton method
*****************************************/
static Dsr::DownloadManager* downloadManagerSharedInstance = nullptr;
DownloadManager* Dsr::DownloadManager::SharedInstance(){
    if(downloadManagerSharedInstance == nullptr){
        downloadManagerSharedInstance = new Dsr::DownloadManager();
    }
    return downloadManagerSharedInstance;
}

/*****************************************
 * Download file
*****************************************/
void DownloadManager::downloadFile(QString url, QString filePath) {
    QNetworkRequest request(url);
    QNetworkReply* reply = this->netManager.get(request);

    this->currentDownloads.insert(reply, filePath);
}

/*****************************************
 * Save data to disk
*****************************************/
void DownloadManager::saveToDisk(QNetworkReply *reply){
    QString filePath = this->currentDownloads.value(reply);
    QString fileDir = filePath.left(filePath.lastIndexOf("/"));

    QDir fileDirCheck(fileDir);
    if(!fileDirCheck.exists()) fileDirCheck.mkpath(fileDir);

    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly)){
        //Dsr::Logger::Error(QString("Save To Disk: Failed to open the file! %1").arg(filePath));
    }
    file.write(reply->readAll());
    file.close();
}

/*****************************************
 * Save data to disk
*****************************************/
QMap<QNetworkReply*, QString>* Dsr::DownloadManager::getCurrentDownloads(){
    return &this->currentDownloads;
}

/*****************************************
 * Download finished slot
*****************************************/
void DownloadManager::downloadFinished(QNetworkReply *reply){
    // Error
    if(reply->error()){
        //Dsr::Logger::Error(QString("Download failed: %1").arg(reply->errorString()));
    }

    // No error
    else {
        this->saveToDisk(reply);
    }

    currentDownloads.remove(reply);
    reply->deleteLater();

    emit DownloadSaveFinished();
}
