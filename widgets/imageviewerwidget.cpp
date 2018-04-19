#include "imageviewerwidget.h"
#include <QtWidgets>
#include <QImage>

using namespace Dsr;

ImageViewerWidget::ImageViewerWidget()
   : imageLabel(new QLabel)
{
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    imageLabel->setText("DSR");
    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 8);
}

void ImageViewerWidget::SetImage(const QPixmap &newImage)
{

    imageLabel->setPixmap(newImage);

}

void ImageViewerWidget::paintEvent(QPaintEvent *evt){
    QPainter painter(this);

    if (pixmap.isNull()) {
        painter.fillRect(rect(), Qt::white);
        painter.setPen(Qt::black);
        painter.drawText(rect(), Qt::AlignCenter, tr("Rendering initial image, please wait..."));
    }else{
        painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);
    }

}

void ImageViewerWidget::closeEvent(QCloseEvent *event){
    //Dsr::Logger::Info("LiveViewZoom Closed");
    // disconnect signal
    this->disconnect();
    //this->StopLiveViewThread();
    event->accept();
}

void ImageViewerWidget::UpdatePixmap(char *data, int size)
{
    if(!pixmap.loadFromData(QByteArray(data, size))){
        //Dsr::Logger::Info("Pixmap failed to load from data");
        pixmap.fill(QColor("yellow").rgba());
    }

    SetImage(pixmap);
    update();

    // TODO free the data
    // free(data);
}

void ImageViewerWidget::UpdatePixmapFromImage(QString img)
{

    if(!pixmap.load(img)){
        //Dsr::Logger::Info("Pixmap failed to load from data");
        pixmap.fill(QColor("yellow").rgba());
    }

    SetImage(pixmap);
    update();

    // TODO free the data
    // free(data);
}

void ImageViewerWidget::UpdatePixmapFromImage(QByteArray data){

    if(!pixmap.loadFromData(data)){
        pixmap.fill(QColor("yellow").rgba());
    }

    SetImage(pixmap);
    update();

}
