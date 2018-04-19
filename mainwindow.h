#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

namespace Dsr {

class GLWidget;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void setCurrentGlWidget();
    void rotateOneStep();

private:
    enum { NumRows = 2, NumColumns = 3 };

    GLWidget *glWidgets[NumRows][NumColumns];
    GLWidget *currentGlWidget;
};

}
#endif // MAINWINDOW_H
