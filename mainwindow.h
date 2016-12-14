#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <util/sinus.h>
#include <util/dsp.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <util/fourier.h>

#define MAX_GELOMBANG 4

typedef double data_32;
namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
//    sinus *aa;
//    dsp *aa;

    double *xval[MAX_GELOMBANG];
    double *yval[MAX_GELOMBANG];
    double *xval_all;
    double *yval_all;
    double *xval2;
    double *yval2;

    //data spektrum
    double *x_sp;
    double *y_sp;
    double *re_out;
    double *img_out;
    double *Amod;
    //magnitude
    double *y_mgt;

    double lines;
//    int point;

    double f,f2,a,a2,point;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void cek_sin();
    void do_fft();


private slots:
    void on_t_start_clicked();    


//    void on_t_stop_pressed();

private:
    Ui::MainWindow *ui;
    QwtPlot *plot1,*plot2,*plot3;
    QwtPlotCurve *kurva1,*kurva2,*kurva3, *kurva4;

    dsp *sig;
    void buffer();
    void buat_windowfilter(int tipe);
//    void clearbuffer();

};

#endif // MAINWINDOW_H
