#include "imageprocessor.h"
#include <QFileDialog>
#include <iostream>
#include<qmath.h>

using namespace std;

QString ImageProcessor::getName() const
{
    return name;
}

void ImageProcessor::setName(const QString &value)
{
    name = value;
}

void ImageProcessor::setImage(Image *value)
{
    type=value->getType();
    image = value;
}
ImageProcessor::ImageProcessor()
{

}

Image* ImageProcessor::openImage(QString path){


    //get image type
    type =path.split(".").back();

    //get file name
    name=path.split("/").back();
    //load image
    this->image = new Image(path);

    return this->image;
}

Image* ImageProcessor::cloneImage(Image* image){
    Image* newimage=new Image();
    newimage->setHeight(image->getHeight());
    newimage->setWidth(image->getWidth());
    newimage->setPixels(image->getPixels());
    newimage->setName(image->getName());
    newimage->setType(image->getType());
    return newimage;
}
Image* ImageProcessor::cloneImage(){
    Image *image=new Image();
    image->setHeight(this->image->getHeight());
    image->setWidth(this->image->getWidth());
    image->setPixels(this->image->getPixels());
    image->setName(this->image->getName());
    image->setType(this->image->getType());
    return image;
}

QPixmap* ImageProcessor::getDrawableImag(){
    return this->image->getDrawable();
}
QImage* ImageProcessor::getDrawableImage(){
    return this->image->getDrawableImage();
}
QPixmap ImageProcessor::getDrawableImag(int a){
    return this->image->getDrawable(0);
}


bool ImageProcessor::saveAs(QString type,QString filePath){

    type=type.split("*").at(1);//remove *
    type=type.split(")").at(0);//remove )

    cout<<"Path: "<< filePath.toStdString()+type.toStdString()<<endl;
    QImage img = image->getWritable();
    img.save(filePath+type,0,-1);
    return true;
}

bool ImageProcessor::save(){
    QImage img = image->getWritable();
    img.save(path+"."+type,0,-1);
    return true;
}

void ImageProcessor::setPath(QString path){
    this->path=path;
}

void ImageProcessor::setType(QString type){
    this->type=type;
}

QString ImageProcessor::getPath()
{
    return path;
}

void ImageProcessor::negative(){
    int newR;
    int newG;
    int newB;
    for(int i=0;i<image->getHeight();i++){
        for(int j=0;j<image->getWidth();j++){
            newR = 255-image->getPixel(i,j).R;
            newG = 255-image->getPixel(i,j).G;
            newB = 255-image->getPixel(i,j).B;
            image->setPixel(i,j,newR,newG,newB);
        }
    }
}

void ImageProcessor::scale(double scale, int method){

    Pixel pixel;
    int h=(image->getHeight()*scale);
    int w=(image->getWidth()*scale);
    Image* tmpimage=new Image(h,w);
    //    Image tmpImage;
    //    tmpimage->setHeight(h);
    //    tmpimage->setWidth(w);
    tmpimage->setName(image->getName());
    tmpimage->setType(image->getType());
    cout<<"h"<<h<<" w"<<w<<" scale:"<<scale<<endl;
    for (int i=0;i<h;i++) {
        //cout<<i<<";"<<qFloor((i)/scale)<<endl;
        for (int j=0;j<w;j++) {

            pixel =image->getPixel(qFloor((i)/scale),qFloor((j)/scale));
            tmpimage->setPixel(i,j,pixel);
            //tmpimage->addPixel(pixel);
        }
    }
    image = tmpimage;
}

Image* tmpImage;
bool adjesting=false;
void ImageProcessor::changeBrightnessContrast(int brightness, int contrast){
    if(!adjesting){
        tmpImage=this->cloneImage();
        adjesting=true;
    }

    //free(tmpImage);
    double cont=((255+contrast))/255.0;cout<<cont<<endl;
    int newR;
    int newG;
    int newB;
    for(int i=0;i<image->getHeight();i++){
        for(int j=0;j<image->getWidth();j++){
            newR = to8bit((tmpImage->getPixel(i,j).R)*cont+brightness);
            newG = to8bit((tmpImage->getPixel(i,j).G)*cont+brightness);
            newB = to8bit((tmpImage->getPixel(i,j).B)*cont+brightness);
            image->setPixel(i,j,newR,newG,newB);
        }
    }cout<<sizeof(*this)<<endl;
    //return tmpImage->getDrawable();
    //return QPixmap::;

}

int ImageProcessor::to8bit(int value){
    if(value>255)
        return 255;
    if(value<0)
        return 0;
    return value;
}
void ImageProcessor::saveChanges(){
    adjesting=false;
}
void ImageProcessor::discardChanges(){
    if(adjesting){
        image=tmpImage;
        adjesting=false;
    }
}

QVector<int> *ImageProcessor::getHistogram(){
    QVector<int>* intensity=new QVector<int>;
    int array[256*3]={0};
    int R;
    int G;
    int B;

    for(int i=0;i<image->getHeight();i++){
        for(int j=0;j<image->getWidth();j++){
            R = image->getPixel(i,j).R;
            G = image->getPixel(i,j).G;
            B = image->getPixel(i,j).B;
            array[R]++;
            array[256+G]++;
            array[256+256+B]++;
//            intensity->at(R);
           // intensity->insert(intensity->at(R)+1,R);
//            intensity[255+G]=8;
//            intensity[255+255+B]++;
           //cout<<intensity->at(R)<<endl;
            //image->setPixel(i,j,newR,newG,newB);
        }
    }
    for(int i=0;i<256*3;i++){
            intensity->push_back(array[i]);
    }
    return intensity;
}
