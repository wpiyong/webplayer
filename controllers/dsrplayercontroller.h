#ifndef DSRPLAYERCONTROLLER_H
#define DSRPLAYERCONTROLLER_H

#include <QObject>
#include <QVector>
#include <QMap>
#include "lib/models/revolutionset.h"
#include <QNetworkReply>
namespace Dsr {

class ImageViewerWidget;
class ApiServices;
class DownloadManager;
class RevolutionDownloadTask;

class DsrPlayerController : public QObject {
    Q_OBJECT
private:
    ImageViewerWidget* imageViewerWidget;
    ApiServices* apiService;
    QVector<RevolutionSet*> rSet;
    QMap<QString, QByteArray> imgsMap;
    QVector<QPair<QString, QByteArray>> imgsVec;
    QVector<int> revosVec;

    int imgIndex;
    int revoIndex;
    int imgTotalIndex;

    bool reverse;
    int size;
    bool revosReady;
    QNetworkAccessManager* networkMgr;
    DownloadManager* downloadMgr;

    void imageViewerControl(Revolution* rev);
    void prepareRevolutionMap();
    int calculateImgTotalIndex(int aImgIndex, int aRevoIndex);
public:
    DsrPlayerController(ImageViewerWidget* aImageViewerWidget, QObject *parent = nullptr);

    void addRevoDownloadTaskToThreadPool(QVector<QString> revolution);
private slots:
    void UpdateImageViewer();
    void RevolutionDownloadTaskFinished(RevolutionDownloadTask*);
    void downloadFinished(QNetworkReply *reply);
signals:
    void UpdatePixmapFromImage(QString img);
    void UpdatePixmapFromImage(QByteArray data);
};

}

#endif // DSRPLAYERCONTROLLER_H
