#ifndef DSP_H
#define DSP_H


class dsp
{
public:
    dsp();

    double buat_sin(double t, int frek, double amp,int geser );
    double gen_wave(int freq, double amp, double *y, double *x, int s_rate, int geser);
    double gen_wave_mod(int freq, double amp, double *y_in,double *y, double *x, int s_rate);

};

#endif // DSP_H
