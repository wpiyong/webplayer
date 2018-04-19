#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QStyle>
#include "./widgets/imageviewerwidget.h"
#include "controllers/dsrplayercontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Dsr::MainWindow w;
    //w.show();

    Dsr::ImageViewerWidget imageViewer;
    Dsr::DsrPlayerController playerCtl(&imageViewer);
    imageViewer.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    //imageViewer.setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, imageViewer.size(), QApplication::desktop()->availableGeometry()));

    imageViewer.show();
    return a.exec();
}
