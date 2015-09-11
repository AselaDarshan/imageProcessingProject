#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <imageprocessor.h>
#include <QVector>
#include "imagewindow.h"
#include "scalingwindow.h"
#include "bcadjustmentwindow.h"
#include "histogram.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void filenameSlot(const QString &path);



private slots:

    void on_open_clicked();

    void on_saveAs_clicked();

    void on_save_clicked();



    void on_clone_clicked();

    void windowSelected(int id);
    void negative_clicked();
    void scale_clicked();
    void scale(double scale, int method, bool ok);
    void bright_constr_clicked();
    void histogram_clicked();
    void bright_constr_windowClosed(bool);

private:
    QVector<ImageWindow*> imageWindows;
    int currentWindow;
    int numberOfWindows;
    Ui::MainWindow *ui;
   // ImageProcessor imageProcessor;
    scalingWindow* scaleWindow;\
    BCadjustmentWindow* brightContWindow;


};

#endif // MAINWINDOW_H
