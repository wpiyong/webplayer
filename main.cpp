#include "mainwindow.h"
#include <QApplication>
#include "./widgets/imageviewerwidget.h"
#include "controllers/dsrplayercontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Dsr::MainWindow w;
    //w.show();

    Dsr::ImageViewerWidget imageViewer;
    Dsr::DsrPlayerController playerCtl(&imageViewer);
    imageViewer.show();
    return a.exec();
}
