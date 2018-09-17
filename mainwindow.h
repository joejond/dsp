#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QMainWindow>
#include <QLabel>
//#include <QString>

#include <util/sinus.h>
#include <util/dsp.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <util/fourier.h>
#include "time_t.h"

#define MAX_GELOMBANG 4
#define MAX_PLOT 10

#define FAKTOR_RMS_HANN     1.225019984
#define FAKTOR_RMS_BLACK    1.3592304768
#define FAKTOR_RMS_RECT     0.7501077976
#define FAKTOR_RMS_HAMM     1.1900016639


//class QString;
//QString datta;


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

    double *xval_wind;
    double *yval_wind;

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
    QString data_waktu;

    double *window_koef;
    double faktor_rms;

    int tipe_wind;



public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    time_tt *disp_time;



    void cek_sin();
    void do_fft();
    QLabel *tulis;
    //extern QString buff_timenya;

 public slots:
    void simpanTime();

signals:

private slots:
    void on_t_start_clicked();    


//    void on_t_stop_pressed();

    void on_show_window_filter_stateChanged(int arg1);

    void on_combo_window_tipe_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QwtPlot *plot1,*plot2,*plot3;
    QwtPlot *plot[MAX_PLOT];
    QwtPlotCurve *kurva[MAX_PLOT];
    QwtPlotCurve *kurva1,*kurva2,*kurva3, *kurva4;


    dsp *sig;
    void buffer();
    void buat_windowfilter(int tipe);
    void do_window();
    void initGrafik();
//    void do_plot_middle(bool cek);

//private slots:
//    void clearbuffer();

};

#endif // MAINWINDOW_H
