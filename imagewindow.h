#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QFileDialog>
#include <QDockWidget>

#include <iostream>

#include <imageprocessor.h>


class CustomDockWidget:public QDockWidget{
    void mousePressEvent(QMouseEvent* event);
};
class ImageWindow:public QWidget
{
    Q_OBJECT
private:
    int windowID;
    ImageProcessor* imageProcessor;

    QGraphicsScene *scene;
    QGraphicsPixmapItem *item;
    QGraphicsView *view;
    CustomDockWidget *dock;
    QWidget* parent;
public:
    ImageWindow(int id,QWidget* parent);

    CustomDockWidget* openWindow();
    CustomDockWidget* openWindow(Image* image);
    void negative();
    Image *getClone();
    void save();
    void saveAs(QString type, QString path);
    void select();
    void deSelect();
    void scale(double scale,int method);
    void discardChanges();
    void saveChanges();

    void getHistogram(QVector<int>* histogram);

private slots:
    void focusChanged(bool focused);
    void changeBrightCont(int,int);
signals:
    void selectThis(int id);
};

#endif // IMAGEWINDOW_H
