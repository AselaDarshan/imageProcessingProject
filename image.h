#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QPixmap>

struct Pixel{
    int R;
    int G;
    int B;
};

class Image
{
private:
    int width;
    int height;
    std::vector<Pixel> pixels;
    QString name;
    QString type;
    QPixmap* pm;
    QImage* im;
    uchar* rawData;

public:
    Image();
    ~Image();
    Image(int height, int width);
    Image(QString path);
    int getHeight();
    int getWidth();

    std::vector<Pixel> getPixels();

    void setWidth(int value);
    void setHeight(int value);
    void setPixels(const std::vector<Pixel> &value);
    void setPixel(int x,int y,int r,int g,int b);
    void setPixel(int x,int y,Pixel pixel);
    void addPixel(Pixel pixel);
    Pixel getPixel(int x,int y);

    QPixmap *getDrawable();
    QImage *getDrawableImage();
    QPixmap getDrawable(int);
    QImage getWritable();

    QString getName() const;
    void setName(const QString &value);

    QString getType() const;
    void setType(const QString &value);

private:
    int getPotition(int h, int w);
};

#endif // IMAGE_H
