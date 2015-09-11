#include "bcadjustmentwindow.h"
#include "ui_bcadjustmentwindow.h"
#include "string"

using namespace std;
BCadjustmentWindow::BCadjustmentWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BCadjustmentWindow)
{
    ui->setupUi(this);

     connect(ui->brightnesSlider,SIGNAL(valueChanged(int)),this,SLOT(brightChange(int)));
     connect(ui->brightnessEdit,SIGNAL(textChanged(QString)),this,SLOT(brightChange(QString)));
     connect(ui->contrastSlider,SIGNAL(valueChanged(int)),this,SLOT(contrastChange(int)));
     connect(ui->contrastEdit,SIGNAL(textChanged(QString)),this,SLOT(contrastChange(QString)));
     saveCanges=false;
}

BCadjustmentWindow::~BCadjustmentWindow()
{
    delete ui;
    emit closed(saveCanges);
}

void BCadjustmentWindow::brightChange(int value){

    ui->brightnessEdit->setText(QString::number(value));
    emit bright_cont_Changed(ui->brightnesSlider->value(),ui->contrastSlider->value());
}
void BCadjustmentWindow::brightChange(QString value){

    ui->brightnesSlider->setValue(value.toInt());
}
void BCadjustmentWindow::contrastChange(int value){

    ui->contrastEdit->setText(QString::number(value));
    emit bright_cont_Changed(ui->brightnesSlider->value(),ui->contrastSlider->value());

}
void BCadjustmentWindow::contrastChange(QString value){

    ui->contrastSlider->setValue(value.toInt());

}

void BCadjustmentWindow::on_ok_clicked()
{
    saveCanges=true;
    this->close();
    this->~BCadjustmentWindow();
}

void BCadjustmentWindow::on_cancel_clicked()
{
    saveCanges=false;
    this->close();
    this->~BCadjustmentWindow();
}
