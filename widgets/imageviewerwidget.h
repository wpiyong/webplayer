#ifndef IMAGEVIEWERWIDGET_H
#define IMAGEVIEWERWIDGET_H

#include <QMainWindow>
#include <QImage>
#include <QCloseEvent>
#include <QLabel>

namespace Dsr {

class ImageViewerWidget : public QMainWindow
{
    Q_OBJECT

public:
    ImageViewerWidget();

public slots:

    void UpdatePixmap(char *data, int size);
    void UpdatePixmapFromImage(QString img);
    void UpdatePixmapFromImage(QByteArray data);
protected:
    //
    //  Event overrides
    //
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    void SetImage(const QPixmap &newImage);

    QLabel *imageLabel;
    QPixmap pixmap;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};


}
#endif // IMAGEVIEWERWIDGET_H
