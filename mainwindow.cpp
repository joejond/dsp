#define MODULASI 0

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "util/sinus.h"
#include "util/fourier.h"

#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QThread>
#include <QString>
#include <QObject>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include "time_t.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Analisis Digital"); //nama window

    disp_time = new time_tt;
    QTimer *udTime = new QTimer(this);
    QObject::connect(udTime, SIGNAL(timeout()), this, SLOT(simpanTime()));
    udTime->start(1000);
    ui->isi_amp->setSingleStep(0.1);        //mengganti kenaikan pada A1
    ui->isi_amp_2->setSingleStep(0.1);      //mengganti kenaikan pada A2

#if MODULASI
    ui->l_freq->setText("Fm");
    ui->l_freq_2->setText("Fc");
    ui->l_amp->setText("Am");
    ui->l_amp_2->setText("Ac");
#else
    ui->l_index_m->setVisible(false);
    ui->isi_im->setVisible(false);
#endif

    initGrafik();




}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::simpanTime() {
    qDebug() << disp_time->bacaWaktu();
    ui->statusBar->showMessage(disp_time->data_waktu);

}

void MainWindow::initGrafik(){
    plot1 = new QwtPlot();      //plot1 (atas)
    plot2 = new QwtPlot();      //plot2 (tengah)
    plot3 = new QwtPlot();      //plot3 (bawah)
    kurva1 = new QwtPlotCurve(); //wave1
    kurva2 = new QwtPlotCurve(); //wave2
    kurva3 = new QwtPlotCurve(); //wave kawasan waktu -> WaveT
    kurva4 = new QwtPlotCurve(); //wave kawasan frekuensi -> WaveF

    ui->verticalLayout_2->addWidget(plot1);
    ui->verticalLayout_2->addWidget(plot2);
    ui->verticalLayout_2->addWidget(plot3);

    kurva1->setPen(Qt::red);    //warna wave1
    kurva1->attach(plot1);      //wave1 digambar di plot1
    kurva2->setPen(Qt::blue);   //warna wave2
    kurva2->attach(plot1);      //wave2 digambar di plot1
    kurva3->setPen(Qt::green);  //warna WaveT
    kurva3->attach(plot2);      //waveT digambar di plot2
    kurva4->setPen(Qt::yellow); //warna WaveF
    kurva4->attach(plot3);      //waveF digambar di plot3


    plot1->setMaximumHeight(200);                       //tinggi plot1 (default:200)
    plot1->setPalette(Qt::white);                       //background plot1
    plot1->setAxisTitle(QwtPlot::yLeft,"Amplitude");    //keterangan nama plot1 vertikal
    plot1->setAxisTitle(QwtPlot::xBottom,"Time");      //keterangan nama plot1 horizontal
    plot2->setMaximumHeight(200);                       //tinggi plot2 (default:200)
    plot2->setPalette(Qt::white);                       //background plot2
    plot2->setAxisTitle(QwtPlot::yLeft,"Amplitude");    //keterangan nama plot2 vertikal
    plot2->setAxisTitle(QwtPlot::xBottom,"Time");      //keterangan nama plot2 horizontal
    plot3->setMaximumHeight(200);                       //tinggi plot3 (default:200)
    plot3->setPalette(Qt::white);                       //background plot3
    plot3->setAxisTitle(QwtPlot::yLeft,"Amplitude");    //keterangan nama plot3 vertikal
    plot3->setAxisTitle(QwtPlot::xBottom,"Frekuensi");  //keterangan nama plot3 horizontal

    QwtPlotGrid *grid1 = new QwtPlotGrid();             //grid pada plot1 name : grid1
    grid1->setPen(QPen(Qt::gray,0.0,Qt::DotLine));      //detail grid plot1 : warna gray, besarnya 0.0, tipe DotLine
    grid1->enableX(true);                               //grid X ditampilkan
    grid1->enableY(true);                               //grid y ditampilkan
    grid1->attach(plot1);                               //grid1 digambar di plot1

    QwtPlotGrid *grid2 = new QwtPlotGrid();             //grid pada plot2 name : grid2
    grid2->setPen(QPen(Qt::gray,0.0,Qt::DotLine));
    grid2->enableX(true);
    grid2->enableY(true);
    grid2->attach(plot2);

    QwtPlotGrid *grid3 = new QwtPlotGrid();             //grid pada plot3 name : grid3
    grid3->setPen(QPen(Qt::gray,0.0,Qt::DotLine));
    grid3->enableX(true);
    grid3->enableY(true);

    grid3->attach(plot3);
}

void MainWindow::buffer(){
    xval[0] = new double[(int) point];
    yval[0] = new double[(int) point];
    xval[1] = new double[(int) point];
    yval[1] = new double[(int) point];
    xval_all = new double[(int) point];
    yval_all = new double[(int) point];
    y_mgt = new double[(int) point];
    x_sp = new double[(int) point];
    re_out = new double[(int) point];
    img_out = new double[(int) point];

    Amod = new double[(int) point];
}

void MainWindow::on_t_start_clicked()
{
    f = ui->isi_frek->text().toDouble();
    f2 = ui->isi_frek_2->text().toDouble();
    a = ui->isi_amp->value();
    a2 = ui->isi_amp_2->value();
    point = ui->combo_sample->currentText().toDouble();
    lines = point / 2.56;
//    qDebug("a = %f, a2= %f",a,a2);
    int j;

    this->buffer();




#if MODULASI
    qDebug() << "Mulai Modulasi";
    double index = a/a2;

    QString im;
    im.sprintf("%.2f",index);

    ui->isi_im->setText(im);

    /* signal yang dimodulasi   misal 20 Hz*/
    this->sig->gen_wave(f,a,yval[0],xval[0],point,0);

    /*dmodulasi dengan signal carrier 200Hz*/
    this->sig->gen_wave_mod(f2,a2,yval[0],yval[1],xval[1],point);
    kurva1->setRawSamples(xval[0],yval[0],point+1);
    kurva3->setRawSamples(xval[1],yval[1],point+1);
#else
    this->sig->gen_wave(f,a,yval[0],xval[0],point,0);
    this->sig->gen_wave(f2,a2,yval[1],xval[1],point,0);
    /*sinus gabungan all*/
    double pecahan = (double) (1.0)/(point);
    for(j=0;j<point+1;j++){
        xval_all[j] = j * pecahan;
        yval_all[j] = yval[0][j] + yval[1][j];
//        qDebug("xval[%d] = %f",j,yval_all[j]);
    }

    kurva1->setRawSamples(xval[0],yval[0],point+1);
    kurva2->setRawSamples(xval[1],yval[1],point+1);
    kurva3->setRawSamples(xval_all,yval_all,point+1);


#endif

    plot1->replot();
    plot2->replot();

    this->do_fft();
    kurva4->setRawSamples(x_sp,y_mgt,lines);
    plot3->replot();


}

void MainWindow::do_fft(){


    /* Untuk skala y, ymag = (sqrt(real^2 + img^2) / point ) * 2
    *
    */
#if MODULASI

    fft_double(point,0,yval[1],0,re_out,img_out);
#else
    fft_double(point,0,yval_all,0,re_out,img_out);
#endif
    int i;
    for(i=0;i<lines;i++){
        y_mgt[i] = (double) (sqrt((re_out[i] * re_out[i]) + (img_out[i] * img_out[i]))/(point)) *2 ;
        x_sp[i] = (double) (i * 1.0);
    }




}

void MainWindow::buat_windowfilter(int tipe){
    if (tipe & 1){
        qDebug() << "tipe window 1";
    }
    else if (tipe & 2) {
        qDebug() << "tipe window 2";
    }
    else if (tipe & 3){
        qDebug() << "tipe window 3";

    }
    else qDebug() << "tipe window 4";
}
