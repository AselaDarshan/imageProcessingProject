#ifndef SCALINGWINDOW_H
#define SCALINGWINDOW_H

#include <QMainWindow>

namespace Ui {
class scalingWindow;
}

class scalingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit scalingWindow(QWidget *parent = 0);
    ~scalingWindow();

private:
    Ui::scalingWindow *ui;
signals:
    void windowClosed(double scale,int method,bool ok);
private slots:
    void on_ok_clicked();
    void on_cancel_clicked();
};

#endif // SCALINGWINDOW_H
