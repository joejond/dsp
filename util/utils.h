#ifndef UTILS_H
#define UTILS_H


#ifdef __cplusplus
extern "C" {
#endif

/* data plot 32 bit / floating point

    setting ini perlu ngecek ke library QWT
    yang ada di set_haliza.h
    di :
    /home/jadid/QtSDK_1.2.1/libku/qwt-6.0.0_float/src/
*/
#define DT_PLOT_32  0

#if (DT_PLOT_32 == 1)
typedef float data_32;
#else
/* data plot dll pakai 64 bit / double precision */
typedef double data_32;
#endif

typedef struct
{
    data_32 maks;
    data_32 min;
    data_32 x_maks;
    data_32 x_min;
    int i_maks;
    int i_min;
} t_marker;


data_32 get_maks(data_32 *in, int len);
data_32 get_min(data_32 *in, int len);
int get_marker(data_32 *in, data_32 *in_x, int len, t_marker *tm);
int get_i_maks(data_32 *in, int len);

int buat_sinus(double frek, double *sinout, double range, int def_sampling_rate, double dc, int geser);
int buat_pulsa(double frek, double *sinout, double range, int def_sampling_rate, double dc, int geser);

int hitung_fase_pickup(double *in, int awal, int akhir, int len, int flag);
double rata_fase(double *in, int len);
double rata_fase_antar_ch(double *in, int len);
int cari_trigger_dari_pulsa(double *in, int len, int *trig, int *len_360, int *len_720);


char *get_jam(void);
char *get_tahun(void);
char *get_tahun_tim( unsigned long tim );
char *get_jam_tim( unsigned long tim);

#ifdef __cplusplus
}
#endif


#endif // UTILS_H
