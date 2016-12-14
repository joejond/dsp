#ifndef WINDOW_FILTER_H
#define WINDOW_FILTER_H

//#define USE_HP
//#include "util/utils.h"

#ifdef __cplusplus
extern "C" {
#endif

#define faktor_hanning		0.5
#define faktor_hamming		0.54

/* lihat di itung_rms.c dan /home/jadid/document/kalibrasi_haliza_10_simul */
#define FAKTOR_RMS_HANN     1.225019984
#define FAKTOR_RMS_BLACK    1.3592304768
#define FAKTOR_RMS_RECT     0.7501077976
#define FAKTOR_RMS_HAMM     1.1900016639


void buat_hanning(data_32 *out, int M);
void buat_hamming(data_32 *out, int M);
void buat_blackman(data_32 *out, int M);
void buat_rectangular(data_32 *out, int M);
void skala_window(data_32 *out, int M, data_32 faktor);
#if 0
int buat_bandpass(data_32 *out, int M, data_32 fc_L, data_32 fc_H, unsigned short kind);

data_32 calc_rms(data_32 *in, int n);
data_32 digital_rms(data_32 *in, int n, data_32 faktor);
data_32 digital_rms_1(data_32 *in, int n);


/* ada di filter_lib.c */
#define DEF_PJG_KERNEL      101

enum filterType {LOW_PASS, HIGH_PASS, BAND_PASS, BAND_STOP};
enum windowType {RECTANGULAR, BARTLETT, HANNING, HAMMING, BLACKMAN};

//#ifdef __i386__
#ifdef __x86_64__
typedef double doubledd;
#else
//typedef float doubledd;
typedef double doubledd;
#endif


void siapkan_filter(int s_rate, int f_start, int f_stop, int tipe_window);
void proses_konvolusi(doubledd *in, doubledd *out, int size, doubledd *akhir);
doubledd *create1TransSinc(int windowLength, doubledd transFreq, doubledd sampFreq, enum filterType type);
//doubledd *create2TransSinc(int windowLength, doubledd trans1Freq, doubledd trans2Freq, doubledd sampFreq, enum filterType type);
doubledd *create2TransSinc22(int windowLength, doubledd trans1Freq, doubledd trans2Freq, doubledd sampFreq, enum filterType type, doubledd *win);
void konvolusi( doubledd *in, doubledd *out, doubledd *kernel, int kernel_size, int in_size, doubledd *akhiran);


/* akhir dari fungsi di filter_lib.c */

/* ada di filter_iir.c */
void hitung_koef_IIR_velocity(unsigned int srate, doubledd *p_a0, doubledd *p_b1);
#endif
#ifdef __cplusplus
}
#endif

#endif // WINDOW_FILTER_H
