#include "image.h"
#include <iostream>
using namespace std;


QString Image::getName() const
{
    return name;
}

void Image::setName(const QString &value)
{
    name = value;
}

QString Image::getType() const
{
    return type;
}

void Image::setType(const QString &value)
{
    type = value;
}
Image::Image(){
}
Image::Image(int height,int width){
    Pixel pixel;
    pixel.R=0;
    pixel.G=0;
    pixel.B=0;
    for(int i=0;i<width*height;i++)
        pixels.push_back(pixel);
    this->width=width;
    this->height=height;
}
Image::Image(QString path)
{
    //open image
    QImage image(path);

    //set image size
    this->height=image.height();
    this->width=image.width();

    this->setName(path.split("/").last());
    this->setType(path.split(".").last());
    //extract RGB data from raw data and store it in pixel array
    cout<<image.format();
    image = image.convertToFormat(QImage::Format_RGB888);
    uchar* rawData = image.bits();
    Pixel tmp;
    for(int i=0;i<height*width*3;i+=3){
        tmp.R = rawData[i];
        tmp.G = rawData[i+1];
        tmp.B = rawData[i+2];
        pixels.push_back(tmp);
    }
     pm=new QPixmap();
}

std::vector<Pixel> Image::getPixels(){
    return pixels;
}

int Image::getHeight(){
    return height;
}

int Image::getWidth(){
    return width;
}

void Image::setWidth(int value)
{
    width = value;
}

void Image::setHeight(int value)
{
    height = value;
}

void Image::setPixels(const std::vector<Pixel> &value)
{
    for(uint i=0;i<value.size();i++)
    {
        pixels.push_back(value.at(i));
    }
}

QPixmap* Image::getDrawable(){
    rawData=(uchar*)malloc(height*width*3);

    //image = image.convertToFormat(QImage::Format_RGB888);
    Pixel tmp;
    int PixelCount=0;
    for(int i=0;i<height*width*3;i+=3){
        tmp=pixels.at(PixelCount++);
        rawData[i]=tmp.R;
        rawData[i+1]=tmp.G;
        rawData[i+2]=tmp.B;

    }
    im=new QImage(rawData,width,height,QImage::Format_RGB888);
    cout<<im->isNull();
    //im.fromData(rawData,width,height,QImage::Format_RGB888);
    //im.fromData(rawData,height,width,QImage::Format_RGB888);
    //cout<<height<<"x"<<width;
   // m=QPixmap::fromImage(*im);
    pm->fromImage(*im);//=&(QPixmap::fromImage(im).);
   // im.~QImage();
   // free(rawData);
   // cout<<"\npm:"<<pm->isNull()<<" m:"<<m.isNull()<<endl;
    return pm;
}
QImage* Image::getDrawableImage(){
    QPixmap* pm;
    QImage* im;
    uchar* rawData;
    rawData=(uchar*)malloc(height*width*3);

    //image = image.convertToFormat(QImage::Format_RGB888);
    Pixel tmp;
    int PixelCount=0;
    for(int i=0;i<height*width*3;i+=3){
        tmp=pixels.at(PixelCount++);
        rawData[i]=tmp.R;
        rawData[i+1]=tmp.G;
        rawData[i+2]=tmp.B;

    }
    im=new QImage(rawData,width,height,QImage::Format_RGB888);
    cout<<im->isNull();
    //im.fromData(rawData,width,height,QImage::Format_RGB888);
    //im.fromData(rawData,height,width,QImage::Format_RGB888);
    //cout<<height<<"x"<<width;
   // m=QPixmap::fromImage(*im);
    pm->fromImage(*im);//=&(QPixmap::fromImage(im).);
   // im.~QImage();
   // free(rawData);
    //cout<<"\npm:"<<pm->isNull()<<" m:"<<m.isNull()<<endl;
    return im;
}
QPixmap Image::getDrawable(int a){
    uchar* rawData=(uchar*)malloc(height*width*3);

    //image = image.convertToFormat(QImage::Format_RGB888);
    Pixel tmp;
    int PixelCount=0;
    for(int i=0;i<height*width*3;i+=3){
        tmp=pixels.at(PixelCount++);
        rawData[i]=tmp.R;
        rawData[i+1]=tmp.G;
        rawData[i+2]=tmp.B;

    }
    QImage im(rawData,width,height,QImage::Format_RGB888);
    //im.fromData(rawData,height,width,QImage::Format_RGB888);
    //cout<<height<<"x"<<width;

    pm->fromImage(im);//=&(QPixmap::fromImage(im).);
    //im.~QImage();
    //free(rawData);
    return QPixmap::fromImage(im);
}
QImage Image::getWritable(){
    uchar* rawData=(uchar*)malloc(height*width*3);

    //image = image.convertToFormat(QImage::Format_RGB888);
    Pixel tmp;
    int PixelCount=0;
    for(int i=0;i<height*width*3;i+=3){
        tmp=pixels.at(PixelCount++);
        rawData[i]=tmp.R;
        rawData[i+1]=tmp.G;
        rawData[i+2]=tmp.B;

    }
    QImage im(rawData,width,height,QImage::Format_RGB888);
    return im;
}

void Image::setPixel(int h, int w, int r, int g, int b){
    Pixel tmp;
    tmp.R =r;
    tmp.G =g;
    tmp.B =b;
    pixels[getPotition(h,w)]=tmp;
}

void Image::setPixel(int h, int w,Pixel pixel){
    pixels[getPotition(h,w)]=pixel;
}
Pixel Image::getPixel(int h, int w){
    return pixels.at(getPotition(h,w));
}

int Image::getPotition(int h, int w){
    return h*(width)+w;
}
void Image::addPixel(Pixel pixel){
    pixels.push_back(pixel);
}

Image::~Image(){

}
