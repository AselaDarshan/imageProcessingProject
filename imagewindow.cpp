#include "imagewindow.h"

using namespace std;

ImageWindow::ImageWindow(int id,QWidget* parent)
{
    windowID=id;
    imageProcessor = new ImageProcessor();
    scene=new QGraphicsScene();
    item= new QGraphicsPixmapItem();
    view=new QGraphicsView();
    dock = new CustomDockWidget();
    this->parent=parent;


    //dock->setAccessibleDescription();
}
//QString ssheet;
CustomDockWidget* ImageWindow::openWindow(){


    QString filename = QFileDialog::getOpenFileName(this->parent, tr("Open File..."),QString(), tr("Image-Files (*.jpg *.jpeg *.png *.bmp)"));

    //dock = new QDockWidget(tr(filename.split("/").back().toStdString().c_str()),this);

    dock->setWindowTitle(filename.split("/").back());

    dock->setAllowedAreas(Qt::BottomDockWidgetArea);
    ///
    //open image
    imageProcessor->openImage(filename);

    //set image
    //item->setPixmap(*(imageProcessor->getDrawableImag()));
    item->setPixmap(QPixmap::fromImage(*imageProcessor->getDrawableImage()));
    scene->addItem(item);

    view->setScene(scene);
    dock->setWidget(view);
    connect(dock, SIGNAL(topLevelChanged(bool)),this, SLOT(focusChanged(bool)));


    return dock;
}

void ImageWindow::focusChanged(bool focused){
    // cout<<"f:"<<focused<<"->";
    if(focused){
        emit selectThis(this->windowID);

        //cout<<ssheet.toStdString();

    }
    else{

    }
}

Image* ImageWindow::getClone(){
    return imageProcessor->cloneImage();

}
void ImageWindow::negative(){
    imageProcessor->negative();
    item->setPixmap((imageProcessor->getDrawableImag(0)));
    scene->addItem(item);

    view->setScene(scene);
    dock->setWidget(view);
}

CustomDockWidget *ImageWindow::openWindow(Image* image){

    this->imageProcessor->setImage(image);

    dock->setWindowTitle(image->getName()+"-cloned");
    dock->setAllowedAreas(Qt::BottomDockWidgetArea);

    //open image
    // imageProcessor->openImage(filename);

    //set image
    item->setPixmap((imageProcessor->getDrawableImag(0)));
    scene->addItem(item);

    view->setScene(scene);
    dock->setWidget(view);
    //ssheet= dock->styleSheet();
    connect(dock, SIGNAL(topLevelChanged(bool)),this, SLOT(focusChanged(bool)));
    dock->setFloating(true);
    return dock;
}

void ImageWindow::save(){
    if(imageProcessor->getPath().isEmpty()){
        QString path = QFileDialog::getSaveFileName(this->parent, tr("Save"),QString(), tr("JPG(*.jpg);; JPEG(*.jpeg) ;;PNG(*.png);;BMP(*.bmp)"));
        imageProcessor->setPath(path);
    }
    imageProcessor->save();
}

void ImageWindow::saveAs(QString type, QString path){
    imageProcessor->saveAs(type,path);
}

void ImageWindow::select(){

    dock->setFloating(true);

    dock->setStyleSheet("background-color:gray;color: black;font-size: 11pt; font-weight: bold; border: 1px solid darkgray;");
    disconnect(dock, SIGNAL(topLevelChanged(bool)),this, SLOT(focusChanged(bool)));
}
void ImageWindow::deSelect(){

    dock->setStyleSheet("background-color:lightgray;color: gray");
    connect(dock, SIGNAL(topLevelChanged(bool)),this, SLOT(focusChanged(bool)));
}
void CustomDockWidget::mousePressEvent(QMouseEvent* event){

    emit topLevelChanged(true);
}

void ImageWindow::scale(double scale, int method){
    imageProcessor->scale(scale,method);
    scene=new QGraphicsScene();
    item= new QGraphicsPixmapItem();
    item->setPixmap((imageProcessor->getDrawableImag(0)));
    scene->addItem(item);
    view->setScene(scene);
}

void ImageWindow::changeBrightCont(int brightness, int contrast){


    imageProcessor->changeBrightnessContrast(brightness,contrast);

    item->setPixmap((imageProcessor->getDrawableImag(0)));


}

void ImageWindow::saveChanges(){
    imageProcessor->saveChanges();
}
void ImageWindow::discardChanges(){
    imageProcessor->discardChanges();
    item->setPixmap(imageProcessor->getDrawableImag(0));
}
void ImageWindow::getHistogram(QVector<int> *histogram){
    QVector<int>* histo= imageProcessor->getHistogram();
    for(int i=0;i<256*3;i++)
        histogram->insert(i,histo->at(i));
    //return imageProcessor->getHistogram();
}
