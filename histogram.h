#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QMainWindow>
#include <QVector>
#include <iostream>
namespace Ui {
class Histogram;
}

class Histogram : public QMainWindow
{
    Q_OBJECT
private:
    QVector<int>* histogram_data;
    int  max_number_of_pixels=0;
public:
    explicit Histogram(QWidget *parent = 0);
    ~Histogram();
    void setHistogram(QVector<int>* histogram_data);

private:
    Ui::Histogram *ui;

    void plotRedChanel();
    void plotGreenChanel();
    void plotBlueChanel();
    void plotAllChanels();
};

#endif // HISTOGRAM_H
