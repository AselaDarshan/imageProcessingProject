#ifndef BCADJUSTMENTWINDOW_H
#define BCADJUSTMENTWINDOW_H

#include <QMainWindow>
#include <iostream>

namespace Ui {
class BCadjustmentWindow;
}

class BCadjustmentWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BCadjustmentWindow(QWidget *parent = 0);
    ~BCadjustmentWindow();

private:
    Ui::BCadjustmentWindow *ui;
    bool saveCanges;
private slots:
    void brightChange(int);
    void brightChange(QString);
    void contrastChange(int);
    void contrastChange(QString);
    void on_ok_clicked();

    void on_cancel_clicked();

signals:
    void bright_cont_Changed(int,int);
    void contrastChanged(int);
    void closed(bool);
};

#endif // BCADJUSTMENTWINDOW_H
