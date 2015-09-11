#include "scalingwindow.h"
#include "ui_scalingwindow.h"

scalingWindow::scalingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::scalingWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Nearest Neighbour");
    ui->comboBox->addItem("Bilinear interpolation");

}

scalingWindow::~scalingWindow()
{

    delete ui;
}

void scalingWindow::on_ok_clicked()
{
    emit windowClosed(ui->doubleSpinBox->value(),ui->comboBox->currentIndex(),true);
    this->close();
}

void scalingWindow::on_cancel_clicked()
{
     emit windowClosed(ui->doubleSpinBox->value(),ui->comboBox->currentIndex(),false);
    this->close();
}
