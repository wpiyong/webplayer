#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace Dsr {

class DownloadManager : public QObject {
    Q_OBJECT

public:
    // Singleton method
    static DownloadManager* SharedInstance();

    // Other methods
    void downloadFile(QString url, QString filePath);
    void saveToDisk(QNetworkReply* reply);

    // Getters
    QMap<QNetworkReply*, QString>* getCurrentDownloads();

private:
    // Constructor
    explicit DownloadManager(QObject *parent = nullptr);

    // Class variables
    QNetworkAccessManager netManager;
    QMap<QNetworkReply*, QString> currentDownloads;

signals:
    void DownloadSaveFinished();
public slots:
    void downloadFinished(QNetworkReply* reply);

};

}

#endif // DOWNLOADMANAGER_H
