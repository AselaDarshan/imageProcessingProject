#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QFileDialog>
#include <QDockWidget>

#include <iostream>


using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    numberOfWindows = 0;
    currentWindow = 0;
    connect(ui->actionOpen, SIGNAL(triggered()),this, SLOT(on_open_clicked()));
    connect(ui->actionSave, SIGNAL(triggered()),this, SLOT(on_save_clicked()));
    connect(ui->actionSave_as, SIGNAL(triggered()),this, SLOT(on_saveAs_clicked()));
    connect(ui->actionClone, SIGNAL(triggered()),this, SLOT(on_clone_clicked()));
    connect(ui->actionNegative, SIGNAL(triggered()),this, SLOT(negative_clicked()));
    connect(ui->actionScale, SIGNAL(triggered()),this, SLOT(scale_clicked()));
    connect(ui->actionBrightness_contrast, SIGNAL(triggered()),this, SLOT(bright_constr_clicked()));
    connect(ui->actionHistogram, SIGNAL(triggered()),this, SLOT(histogram_clicked()));
    //this->setStyleSheet("background:lightblue");
    ui->saveAs->setVisible(false);
    ui->clone->setVisible(false);
    showMaximized();
    //setCorner(Qt::TopLeftCorner, Qt::BottomDockWidgetArea);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_open_clicked()
{
    ImageWindow* imageWindow = new ImageWindow(numberOfWindows++,this);
    QDockWidget *dock = imageWindow->openWindow();
    addDockWidget(Qt::BottomDockWidgetArea,dock);

    connect(imageWindow, SIGNAL(selectThis(int)),this, SLOT(windowSelected(int)));

    imageWindows.push_back(imageWindow);
    windowSelected(numberOfWindows-1);
    dock->setGeometry(this->geometry().topLeft().x()+50,this->geometry().topLeft().y()+100,dock->size().width(),dock->size().height());

}

QFileDialog *file ;
void MainWindow::on_saveAs_clicked()
{

    file = new QFileDialog(this, tr("Save as..."),QString(), tr("JPG(*.jpg);; JPEG(*.jpeg) ;;PNG(*.png);;BMP(*.bmp)"));

    connect(file, SIGNAL( fileSelected(const QString &)),this, SLOT(filenameSlot(const QString &)));

    file->setAcceptMode(QFileDialog::AcceptSave);
    file->show();


}

void MainWindow::filenameSlot(const QString &path) {
    // text contains the selected filename here
    disconnect(file, SIGNAL( fileSelected(const QString &)),this, SLOT(filenameSlot(const QString &)));
    QString type= file->selectedNameFilter();
    imageWindows[currentWindow]->saveAs(type,path);

}


void MainWindow::on_save_clicked()
{
    if(numberOfWindows>0)
        imageWindows[currentWindow]->save();
}



void MainWindow::on_clone_clicked()
{

    if(numberOfWindows>0){
        ImageWindow* window = new ImageWindow(numberOfWindows++,this);
        QDockWidget *dock = window->openWindow(imageWindows[currentWindow]->getClone());
        addDockWidget(Qt::BottomDockWidgetArea,dock);
        connect(window, SIGNAL(selectThis(int)),this, SLOT(windowSelected(int)));

        imageWindows.push_back(window);
        windowSelected(numberOfWindows-1);
        dock->setGeometry(this->geometry().topLeft().x()+50,this->geometry().topLeft().y()+100,dock->size().width(),dock->size().height());

    }
}

void MainWindow::negative_clicked(){
    if(numberOfWindows>0)
        imageWindows[currentWindow]->negative();
}

void MainWindow::windowSelected(int id){

    imageWindows[currentWindow]->deSelect();

    imageWindows[id]->select();

    currentWindow=id;
}

void MainWindow::scale_clicked(){

    if(numberOfWindows>0){
        scaleWindow=new scalingWindow(this);
        scaleWindow->setWindowFlags(Qt::Dialog);\
        connect(scaleWindow,SIGNAL(windowClosed(double,int,bool)),this,SLOT(scale(double,int,bool)));
        scaleWindow->show();
    }
}

void MainWindow::scale(double scale,int method,bool ok){

    if(ok){
        imageWindows[currentWindow]->scale(scale,method);
    }
}
ImageWindow *tmpImageWindow;
void MainWindow::bright_constr_clicked(){

    if(numberOfWindows>0){
        tmpImageWindow=imageWindows[currentWindow];
        brightContWindow=new BCadjustmentWindow(this);
        brightContWindow->setWindowFlags(Qt::Dialog);\
        connect(brightContWindow,SIGNAL(bright_cont_Changed(int,int)),imageWindows[currentWindow],SLOT(changeBrightCont(int,int)));
        connect(brightContWindow,SIGNAL(closed(bool)),this,SLOT(bright_constr_windowClosed(bool)));

        brightContWindow->show();
    }
}
void MainWindow::bright_constr_windowClosed(bool saveChanges){
    disconnect(brightContWindow,SIGNAL(bright_cont_Changed(int,int)),imageWindows[currentWindow],SLOT(changeBrightCont(int,int)));
    disconnect(brightContWindow,SIGNAL(closed(bool)),this,SLOT(bright_constr_windowClosed(bool)));
    if(saveChanges){
        tmpImageWindow->saveChanges();
    }
    else
        tmpImageWindow->discardChanges();

}
QVector<int>* histogram_data;
Histogram* histogram ;
void MainWindow::histogram_clicked(){
    if(numberOfWindows>0){
        histogram_data=new QVector<int>;
        imageWindows[currentWindow]->getHistogram(histogram_data);
        for(int i=0;i<255;i++)
            std::cout<<histogram_data->at(i)<<endl;
        histogram = new Histogram(this);
        histogram->setHistogram(histogram_data);
        histogram->show();

    }
}
