#include "dsp.h"
#include <QDebug>
#include <QtMath>

dsp::dsp()
{
    qDebug() << "masuk constructor";
}



double dsp::buat_sin(double t, int frek, double amp, int geser ){


    double rad = (double) (2*M_PI*frek);
    double y = (double) (sin(rad * t + geser) * amp);
//    qDebug() << t << freq << rad <<"SIN : "<< y;


    return y;
}




double dsp::gen_wave(int freq, double amp, double *y, double *x, int s_rate, int geser){
    /*s-rate merupakan sampiling rate yang diambil untuk sebuah gelombang*/

    int i;
    for(i=0; i<s_rate+1;i++){
        x[i] = (double)((i*1.0) / s_rate);;
        y[i] = (double) buat_sin(x[i],freq,amp,geser);
        qDebug("x[%d] : %f , y[%d] : %f",i,x[i], i,y[i]);
    }
    return freq;
}

double dsp::gen_wave_mod(int freq, double amp, double *y_in,double *y, double *x, int s_rate){

    int i;
    for(i=0; i<s_rate+1;i++){

        x[i] = (double)((i*1.0) / s_rate);;
        y[i] = (double) buat_sin(x[i],freq,(amp+y_in[i]),0);

//        qDebug("x[%d] : %f , y[%d] : %f",i,x[i], i,y[i]);
    }
    return freq;


}


