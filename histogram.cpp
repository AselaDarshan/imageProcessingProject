#include "histogram.h"
#include "ui_histogram.h"

Histogram::Histogram(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Histogram)
{
    ui->setupUi(this);


}

void Histogram::setHistogram(QVector<int> *histogram_data){
    this->histogram_data=histogram_data;
    for(int i=0;i<256*3;i++){
        if(max_number_of_pixels<histogram_data->at(i))
            max_number_of_pixels=histogram_data->at(i);
    }
    if(max_number_of_pixels>10000)
        max_number_of_pixels=10000;
    plotBlueChanel();
    plotGreenChanel();
    plotRedChanel();
    plotAllChanels();
}
Histogram::~Histogram()
{
    delete ui;
}

void Histogram::plotRedChanel(){
    QCustomPlot *customPlot=this->ui->widget_3;
    srand(98); // set the random seed, so we always get the same random data
    // create multiple graphs:

      customPlot->addGraph();
      QPen pen;
      pen.setColor(QColor(160, 0, 0, 200));
      customPlot->graph()->setLineStyle(QCPGraph::lsLine);
      customPlot->graph()->setPen(pen);
      customPlot->graph()->setBrush(QBrush(QColor(200,0,0,255)));
      customPlot->setBackground(QBrush(QColor(4,2,10,255)));
      // generate random walk data:
      QVector<double> time(256), value(256);
      for (int i=0; i<255; ++i)
      {
        time[i] = i;
        value[i] = this->histogram_data->at(i);


      }
      customPlot->graph()->setData(time, value);

    // configure bottom axis to show date and time instead of number:
    customPlot->xAxis->setTickLabelType(QCPAxis::ltNumber);
   // customPlot->xAxis->setDateTimeFormat("MMMM\nyyyy");
    // set a more compact font size for bottom and left axis tick labels:
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setLabelColor(QColor(251,253,250,255));
    customPlot->xAxis->setLabelColor(QColor(251,253,250,255));
    customPlot->yAxis->setTickLabelColor(QColor(251,253,250,255));
    customPlot->xAxis->setTickLabelColor(QColor(251,253,250,255));
    // set a fixed tick-step to one tick per month:
   // customPlot->xAxis->setAutoTickStep(true);
   // customPlot->yAxis->setAutoTicks(true);
    customPlot->xAxis->setTickStep(5);
    customPlot->xAxis->setSubTickCount(10);
    customPlot->xAxis->setAutoTickLabels(true);
    // apply manual tick and tick label for left axis:
    customPlot->yAxis->setAutoTicks(true);
    customPlot->yAxis->setAutoTickLabels(true);
    // set axis labels:
    customPlot->xAxis->setLabel("Intensity");
    customPlot->yAxis->setLabel("Number of Pixels");
    // make top and right axes visible but without ticks and labels:
    customPlot->xAxis2->setVisible(true);
    customPlot->yAxis2->setVisible(true);
    customPlot->xAxis2->setTicks(false);
    customPlot->yAxis2->setTicks(false);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setTickLabels(false);
    // set axis ranges to show all data:
    customPlot->xAxis->setRange(0, 255);
    customPlot->yAxis->setRange(0, max_number_of_pixels);
    // show legend:
    //customPlot->legend->setVisible(true);
}
void  Histogram::plotGreenChanel(){

    QCustomPlot *customPlot=this->ui->widget;
    srand(8); // set the random seed, so we always get the same random data
    // create multiple graphs:

      customPlot->addGraph();
      QPen pen;
      pen.setColor(QColor(0, 160, 0, 200));
      customPlot->graph()->setLineStyle(QCPGraph::lsLine);
      customPlot->graph()->setPen(pen);
      customPlot->graph()->setBrush(QBrush(QColor(0,200,0,255)));
      customPlot->setBackground(QBrush(QColor(4,2,10,255)));
      // generate random walk data:
      QVector<double> time(255), value(256);
      for (int i=0; i<255; ++i)
      {
        time[i] = i;

          value[i] = histogram_data->at(i+256);

      }
      customPlot->graph()->setData(time, value);

    // configure bottom axis to show date and time instead of number:
    customPlot->xAxis->setTickLabelType(QCPAxis::ltNumber);
   // customPlot->xAxis->setDateTimeFormat("MMMM\nyyyy");
    // set a more compact font size for bottom and left axis tick labels:
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setLabelColor(QColor(251,253,250,255));
    customPlot->xAxis->setLabelColor(QColor(251,253,250,255));
    customPlot->yAxis->setTickLabelColor(QColor(251,253,250,255));
    customPlot->xAxis->setTickLabelColor(QColor(251,253,250,255));
    // set a fixed tick-step to one tick per month:
   // customPlot->xAxis->setAutoTickStep(true);
   // customPlot->yAxis->setAutoTicks(true);
    customPlot->xAxis->setTickStep(5);
    customPlot->xAxis->setSubTickCount(10);
    customPlot->xAxis->setAutoTickLabels(true);
    // apply manual tick and tick label for left axis:
    customPlot->yAxis->setAutoTicks(true);
    customPlot->yAxis->setAutoTickLabels(true);
    // set axis labels:
    customPlot->xAxis->setLabel("Intensity");
    customPlot->yAxis->setLabel("Number of Pixels");
    // make top and right axes visible but without ticks and labels:
    customPlot->xAxis2->setVisible(true);
    customPlot->yAxis2->setVisible(true);
    customPlot->xAxis2->setTicks(false);
    customPlot->yAxis2->setTicks(false);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setTickLabels(false);
    // set axis ranges to show all data:
    customPlot->xAxis->setRange(0, 255);
    customPlot->yAxis->setRange(0, max_number_of_pixels);
    // show legend:
    //customPlot->legend->setVisible(true);
}
void  Histogram::plotBlueChanel(){
    QCustomPlot *customPlot=this->ui->widget_4;
    srand(8); // set the random seed, so we always get the same random data
    // create multiple graphs:

      customPlot->addGraph();
      QPen pen;
      pen.setColor(QColor(0, 0, 160, 200));
      customPlot->graph()->setLineStyle(QCPGraph::lsLine);
      customPlot->graph()->setPen(pen);
      customPlot->graph()->setBrush(QBrush(QColor(0,0,160,255)));
      customPlot->setBackground(QBrush(QColor(4,2,10,255)));
      // generate random walk data:
      QVector<double> time(255), value(256);
      for (int i=0; i<255; ++i)
      {
        time[i] = i;

          value[i] = histogram_data->at(i+256+256);

      }
      customPlot->graph()->setData(time, value);

    // configure bottom axis to show date and time instead of number:
    customPlot->xAxis->setTickLabelType(QCPAxis::ltNumber);
   // customPlot->xAxis->setDateTimeFormat("MMMM\nyyyy");
    // set a more compact font size for bottom and left axis tick labels:
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setLabelColor(QColor(251,253,250,255));
    customPlot->xAxis->setLabelColor(QColor(251,253,250,255));
    customPlot->yAxis->setTickLabelColor(QColor(251,253,250,255));
    customPlot->xAxis->setTickLabelColor(QColor(251,253,250,255));
    // set a fixed tick-step to one tick per month:
   // customPlot->xAxis->setAutoTickStep(true);
   // customPlot->yAxis->setAutoTicks(true);
    customPlot->xAxis->setTickStep(5);
    customPlot->xAxis->setSubTickCount(10);
    customPlot->xAxis->setAutoTickLabels(true);
    // apply manual tick and tick label for left axis:
    customPlot->yAxis->setAutoTicks(true);
    customPlot->yAxis->setAutoTickLabels(true);
    // set axis labels:
    customPlot->xAxis->setLabel("Intensity");
    customPlot->yAxis->setLabel("Number of Pixels");
    // make top and right axes visible but without ticks and labels:
    customPlot->xAxis2->setVisible(true);
    customPlot->yAxis2->setVisible(true);
    customPlot->xAxis2->setTicks(false);
    customPlot->yAxis2->setTicks(false);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setTickLabels(false);
    // set axis ranges to show all data:
    customPlot->xAxis->setRange(0, 255);
    customPlot->yAxis->setRange(0, max_number_of_pixels);
    // show legend:
    //customPlot->legend->setVisible(true);
}

void Histogram::plotAllChanels(){
    QCustomPlot *customPlot=this->ui->widget_2;
    srand(8); // set the random seed, so we always get the same random data
    // create multiple graphs:

      customPlot->addGraph();
      QPen pen;
      pen.setColor(QColor(160, 160,160, 200));
      customPlot->graph()->setLineStyle(QCPGraph::lsLine);
      customPlot->graph()->setPen(pen);
      customPlot->graph()->setBrush(QBrush(QColor(200,200,200,255)));
      customPlot->setBackground(QBrush(QColor(4,2,10,255)));
      // generate random walk data:

      QVector<double> time(255), value(256);
      for (int i=0; i<255; ++i)
      {
        time[i] = i;

          value[i] = (histogram_data->at(i)+histogram_data->at(i+256)+histogram_data->at(i+512))/3;

      }
      customPlot->graph()->setData(time, value);

    // configure bottom axis to show date and time instead of number:
    customPlot->xAxis->setTickLabelType(QCPAxis::ltNumber);
   // customPlot->xAxis->setDateTimeFormat("MMMM\nyyyy");
    // set a more compact font size for bottom and left axis tick labels:
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setLabelColor(QColor(251,253,250,255));
    customPlot->xAxis->setLabelColor(QColor(251,253,250,255));
    customPlot->yAxis->setTickLabelColor(QColor(251,253,250,255));
    customPlot->xAxis->setTickLabelColor(QColor(251,253,250,255));
    // set a fixed tick-step to one tick per month:
   // customPlot->xAxis->setAutoTickStep(true);
   // customPlot->yAxis->setAutoTicks(true);
    customPlot->xAxis->setTickStep(5);
    customPlot->xAxis->setSubTickCount(10);
    customPlot->xAxis->setAutoTickLabels(true);
    // apply manual tick and tick label for left axis:
    customPlot->yAxis->setAutoTicks(true);
    customPlot->yAxis->setAutoTickLabels(true);
    // set axis labels:
    customPlot->xAxis->setLabel("Intensity");
    customPlot->yAxis->setLabel("Number of Pixels");
    // make top and right axes visible but without ticks and labels:
    customPlot->xAxis2->setVisible(true);
    customPlot->yAxis2->setVisible(true);
    customPlot->xAxis2->setTicks(false);
    customPlot->yAxis2->setTicks(false);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setTickLabels(false);
    // set axis ranges to show all data:
    customPlot->xAxis->setRange(0, 255);
    customPlot->yAxis->setRange(0, max_number_of_pixels);
    // show legend:
    customPlot->legend->setVisible(true);
//    customPlot->legend->setIconSize(23,23);
    customPlot->legend->setTextColor(QColor(200,200,255,255));
    customPlot->legend->setBrush(QBrush(QColor(4,2,10,2)));

}
