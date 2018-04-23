#include "imageviewerwidget.h"
#include <QtWidgets>
#include <QImage>
#include "../lib/emprintf.h"

using namespace Dsr;

ImageViewerWidget::ImageViewerWidget()
   : imageLabel(new QLabel)
{
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    //imageLabel->setScaledContents(true);
    imageLabel->setText("DSR");
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
//    imageLabel->setWindowFlags(Qt::Window);
    imageLabel->setScaledContents(true);
//    imageLabel->showFullScreen();
    //resize(QGuiApplication::primaryScreen()->availableSize());
    //int width = 780 * 1.5;
    //int height = 520 * 1.5;
    //resize(780, 520);
    resize(1620, 1080);

    //setCentralWidget(imageLabel);
}

void ImageViewerWidget::SetImage(const QPixmap &newImage)
{

    int w = imageLabel->width();
    int h = imageLabel->height();
    ::emprintf("ImageViewerWidget setImage, label width: %d, height: %d: ", w, h);
    // set a scaled pixmap to a w x h window keeping its aspect ratio
    imageLabel->setPixmap(newImage.scaled(w, h, Qt::KeepAspectRatio));
    //imageLabel->setPixmap(newImage);

}

void ImageViewerWidget::resizeEvent(QResizeEvent *event) {
    int w = imageLabel->width();
    int h = imageLabel->height();

    // set a scaled pixmap to a w x h window keeping its aspect ratio
    imageLabel->setPixmap(pixmap.scaled(w, h, Qt::KeepAspectRatio));
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
