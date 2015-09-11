#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QVector>
#include <image.h>



class ImageProcessor
{
private:
    Image* image;
    QString path;
    QString type;
    QString name;
public:
    ImageProcessor();
    Image *openImage(QString path);
    Image *cloneImage(Image *image);
    Image *cloneImage();
    QPixmap *getDrawableImag();
    QImage *getDrawableImage();
    QPixmap getDrawableImag(int);
    bool saveAs(QString type,QString path);
    bool save();
    void setPath(QString path);
    void setType(QString type);
    QString getType();
    QString getPath();
    QString getName() const;
    void setName(const QString &value);

    void negative();
    void setImage(Image *value);
    void scale(double scale,int method);
    void changeBrightnessContrast(int brightness,int contrast);
    void saveChanges();
    void discardChanges();
    QVector<int>* getHistogram();
    int to8bit(int);
};

#endif // IMAGEPROCESSOR_H
