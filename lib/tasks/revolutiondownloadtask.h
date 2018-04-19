#ifndef REVOLUTIONDOWNLOADTASK_H
#define REVOLUTIONDOWNLOADTASK_H

#include <QObject>
#include <QVector>
#include <QString>

namespace Dsr {

class Revolution;
class DownloadManager;

class RevolutionDownloadTask : public QObject {
    Q_OBJECT

public:
    explicit RevolutionDownloadTask(QVector<QString> aRevolution, int aIndex, QObject *parent = nullptr);

private:
    QVector<QString> revolution;
    int index;
    int count;
    DownloadManager* downloadManager;

public:
    void run();

signals:
    void RevolutionDownloadFinished(RevolutionDownloadTask*);
private slots:
    void DownloadSaveFinished();
};

}

#endif // REVOLUTIONDOWNLOADTASK_H
