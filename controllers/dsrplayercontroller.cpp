#include "dsrplayercontroller.h"
#include <QTimer>
#include <QDebug>
#include <QPixmap>
#include <QBuffer>
#include "../lib/emprintf.h"

#include "../lib/tasks/revolutiondownloadtask.h"
#include "../lib/apiservices.h"
#include "../widgets/imageviewerwidget.h"
#include "../lib/downloadmanager.h"

extern "C" void fetch(char* url, int index);
extern "C" unsigned char *base64_decode(const char *data, size_t input_length, size_t *output_length);
extern "C" int getData(int index);
extern "C" void setData(int value, int index);
extern "C" void prepareNewRevolutionSets();
extern "C" int imgTotal;
extern "C" char** imgUrls;
extern "C" char** imgData;
extern "C" int* list;
extern "C" int listSize;
extern "C" int* imgSize;
extern "C" int imgFinished;
extern "C" int downloadIndex;
extern "C" int newRevolutionSets;
extern "C" int totalRevolutionSets;
extern "C" int listSizeNew;

using namespace Dsr;

DsrPlayerController::DsrPlayerController(ImageViewerWidget* aImageViewerWidget, QObject *parent) : QObject(parent), networkMgr(nullptr), reverse(false), imgIndex(1), revoIndex(0), size(6), revosReady(false), imageViewerWidget(aImageViewerWidget){
    QString clientId = "2bb931d856205a2dd781258bb224a31195fe735200635f03a7f58f9d2e094023";
    QString clientSecret = "5971e6c681ca791473607d3b66cabffd3fc6504587698cb11fd16604d4a44a6e";
    apiService = ApiServices::SharedInstance(clientId, clientSecret);
    //QString token = "de647b18bf8ebc0c1df8427d2430d7e18a903fc2115be522006589cc7b9a3df6";
//    QVector<RevolutionSet*> rSet = apiService->FetchRevolutionSets(token);//apiService->getToken());
//    RevolutionSet *aSet = nullptr;
//    QVector<Revolution*> revs;
    Revolution *aRev = nullptr;
//    if(rSet.size() > 0){
//        aSet = rSet.at(0);
//        revs = aSet->GetRevolutions();
//        aRev = revs.at(0);
//    }
    downloadMgr = DownloadManager::SharedInstance();
    networkMgr = new QNetworkAccessManager(this);
    connect(this, SIGNAL(UpdatePixmapFromImage(QString)), imageViewerWidget, SLOT(UpdatePixmapFromImage(QString)));
    connect(this, SIGNAL(UpdatePixmapFromImage(QByteArray)), imageViewerWidget, SLOT(UpdatePixmapFromImage(QByteArray)));
    //connect(apiService, SIGNAL(DownloadFinished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));
    //connect(networkMgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));
    imageViewerControl(aRev);
}

void DsrPlayerController::imageViewerControl(Revolution* rev){
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateImageViewer()));
    timer->start(83); // 12 frames per seconds
}

int DsrPlayerController::calculateImgTotalIndex(int aImgIndex, int aRevoIndex) {
    int index = aImgIndex;
    for(int i = 0; i < aRevoIndex; i++) {
        index += revosVec.at(i);
    }
    return index;
}

void DsrPlayerController::UpdateImageViewer(){
    if(revosReady) {

        // check new revolution
        if(imgIndex == 0 && newRevolutionSets > 0) {
            ::emprintf("UpdateImageViewer prepareNewRevolutionSets");
            prepareRevolutionOld();
            prepareNewRevolutionSets();
            prepareRevolutionMap();
        }

        imgTotalIndex = calculateImgTotalIndex(imgIndex, revoIndex);
        ::emprintf("UpdateImageViewer image index: %d", imgTotalIndex);
        QPair<QString, QByteArray> pair = imgsVec.at(imgTotalIndex);

        ::emprintf("UpdateImageViewer with revosReady == true, DownloadImage with url: %d", imgSize[imgTotalIndex]);
        if(pair.second.size() == 0) {

            if(imgSize[imgTotalIndex] <= 0) {
                if(downloadIndex != imgTotalIndex) {
                    fetch(imgUrls[imgTotalIndex], imgTotalIndex);
                    downloadIndex = imgTotalIndex;
                }
            } else {
                QByteArray ba(imgData[imgTotalIndex], imgSize[imgTotalIndex]);
                ::emprintf("UpdateImageViewer with data from js, raw data length: %d", imgSize[imgTotalIndex]);
                QPixmap pix;
                pix.loadFromData(ba);

                QPixmap scaledPix = pix.scaled(1620, 1080, Qt::KeepAspectRatio);
                QByteArray bArray;
                QBuffer buffer(&bArray);
                buffer.open(QIODevice::WriteOnly);
                scaledPix.save(&buffer, "JPG");

                imgsVec[imgTotalIndex].second = bArray;

                emit UpdatePixmapFromImage(imgsVec.at(imgTotalIndex).second);
                if( revoIndex % 2 == 0 ) {
                    imgIndex++;
                } else {
                    imgIndex--;
                }
            }

        } else {
            ::emprintf("UpdateImageViewer with revosReady == true, QByteArray size > 0");
            ::emprintf("UpdateImageViewer with revosReady == true, QByteArray size: %d", pair.second.size());
            emit UpdatePixmapFromImage(pair.second);
            if( revoIndex % 2 == 0 ) {
                imgIndex++;
            } else {
                imgIndex--;
            }
        }

        //check if all images in one revolution have displayed
        if(revoIndex % 2 == 0) {
            // even revolution index, imgIndex count up
            if(imgIndex >= revosVec.at(revoIndex)) {
                //imgIndex = 0;
                revoIndex++;
                // check if all revolutions have displayed
                if(revoIndex >= revosVec.size()) {
                    revoIndex = 0;
                }
                if(revoIndex % 2 == 0) {
                    imgIndex = 0;
                } else {
                    imgIndex = revosVec[revoIndex] -1;
                }
            }
        } else {
            // odd revolution index, imgIndex count down
            if(imgIndex < 0) {
                revoIndex++;

                if(revoIndex >= revosVec.size()) {
                    revoIndex = 0;
                }
                if(revoIndex % 2 == 0) {
                    imgIndex = 0;
                } else {
                    imgIndex = revosVec[revoIndex] -1;
                }
            }
        }
    } else {
        QString img = QString(":/images/side%1.png").arg(QString::number(imgIndex));
        emit UpdatePixmapFromImage(img);
        if(reverse){
            if(imgIndex <= 1){
                reverse = false;
                imgIndex++;
            } else {
                imgIndex--;
            }
        } else {
            if(imgIndex >= size){
                reverse = true;
                imgIndex--;
            } else {
                imgIndex++;
            }
        }
    }

//    for(int i = 0; i < 10; i++){
//        ::emprintf("%d", getData(i));
//    }
//    ::emprintf("before: %d", size);

//    size = getData(0);
//    if(size > 6) {
//        size = 6;
//    } else {
//        if(size < 0) {
//            size = 0;
//        }
//    }
//    ::emprintf("after: %d", size);

    if(imgTotal > 0 && listSize > 0 && !revosReady){

        ::emprintf("prepareRevolutionMap");
        ::emprintf("emprintf imgUrls[0]: %s", imgUrls[0]);
        ::emprintf("emprintf imgData[0]: %s", imgData[0]);
        prepareRevolutionMap();
    }
}

void DsrPlayerController::prepareRevolutionOld() {
    // clean map and vector
    for(int i = 0; i < imgsVecOld.size(); i++){
        imgsVecOld[i].second.clear();
        imgsVecOld[i].first.clear();
    }
    revosVecOld.clear();
    imgsVecOld.clear();
    int left = totalRevolutionSets - listSizeNew;
    ::emprintf("prepareRevolutionOld revolutions: %d", left);
    int imgCount = 0;
    for(int i = 0; i < left; i++) {
        revosVecOld.push_back(revosVec[i]);
        imgCount += revosVec[i];
    }
    ::emprintf("prepareRevolutionOld images: %d", imgCount);
    for(int i = 0; i < imgCount; i++) {
        imgsVecOld.push_back(imgsVec[i]);
    }
}

void DsrPlayerController::prepareRevolutionMap() {
    // clean map and vector
    for(int i = 0; i < imgsVec.size(); i++){
        imgsVec[i].second.clear();
        imgsVec[i].first.clear();
    }
    revosVec.clear();
    imgsVec.clear();

    // prepare the maps
    for(int i = 0; i < listSize; i++) {
        revosVec.push_back(list[i]);
    }

    for(int i = 0; i < revosVecOld.size(); i++) {
        revosVec.push_back((revosVecOld[i]));
    }

    for(int i = 0; i < imgTotal; i++) {
        QByteArray data;
        imgsVec.push_back(qMakePair(imgUrls[i], data));
    }

    for(int i = 0; i < imgsVecOld.size(); i++) {
        imgsVec.push_back((imgsVecOld[i]));
    }

    revosReady = true;
    revoIndex = 0;
    imgIndex = 0;

    ::emprintf("prepareRevolutionMap");
}

void DsrPlayerController::addRevoDownloadTaskToThreadPool(QVector<QString> revolution) {
    RevolutionDownloadTask *downloadTask = new RevolutionDownloadTask(revolution, 0);

    connect(downloadTask, SIGNAL(RevolutionDownloadTaskFinished(RevolutionDownloadTask*)), this, SLOT(RevolutionDownloadTaskFinished(RevolutionDownloadTask*)));
    //connect(downloadTask, SIGNAL(UsbExceptionOccurredDuringExecution(CameraAgent*,DsrUsbException*)), this, SLOT(AgentExperiencedUsbError(CameraAgent*,DsrUsbException*)));
    downloadTask->run();
}

void DsrPlayerController::RevolutionDownloadTaskFinished(RevolutionDownloadTask * task){

}

void DsrPlayerController::downloadFinished(QNetworkReply *reply){
    // Error
    QByteArray data;
    // Extract data
//    while(!reply->isFinished()) {
//        ;
//    }
    if(reply->error() == QNetworkReply::NoError){
        ::emprintf("downloadfinished and readAll");
        for(int i = 0; i < 100000; i++){
            ::emprintf("downloadfinished and readAll");
        }
        data = reply->readAll();
        ::emprintf("downloadfinished and readAll data length: %d", data.size());
    }

    reply->deleteLater();
    ::emprintf("downloadFinished with reply qbytearray data");
    imgsVec[0].second = data;
    emit UpdatePixmapFromImage(data);
}
