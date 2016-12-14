/*
 * furkan jadid
 * daun biru engineering
 *
 * 24 April 2013
 * fungsi2 umum
 */

#include "utils.h"
//#include "../low_level/mulai_pru.h"

data_32 get_maks(data_32 *in, int len)
{
    data_32 temp = -1000000.00;
    int i;

    for (i = 0; i<len; i++)
    {
        if ( in[i] > temp) temp = in[i];
    }

    return temp;
}

data_32 get_min(data_32 *in, int len)
{
    data_32 temp = 1000000.00;
    int i;

    for (i = 0; i<len; i++)
    {
        if ( in[i] < temp) temp = in[i];
    }

    return temp;
}

int get_i_maks(data_32 *in, int len)
{
    data_32 temp = -1000000.00;
    int i;
    int r;

    for (i = 0; i<len; i++)
    {
        if ( in[i] > temp)
        {
            temp = in[i];
            r = i;
        }
    }

    return r;
}

/* in adalah sumbu y, in_x untuk sumbu x */
int get_marker(data_32 *in, data_32 *in_x, int len, t_marker *tm)
{
    int i;
    tm->maks = -4000000000.00;
    tm->min = 4000000000.00;

    for (i=0; i<len; i++)
    {
        if (in[i] > tm->maks)
        {
            tm->maks = in[i];
            tm->x_maks = in_x[i];
            tm->i_maks = i;
        }
        if (in[i] < tm->min)
        {
            tm->min = in[i];
            tm->x_min = in_x[i];
            tm->i_min = i;
        }
    }

    return 0;
}

/*
    mencari sudut fasa sinyal in, dibanding dengan posisi pickup
    karena pakai pikcup, maka dianggap lebar yang valid adalah
    selebar pickup.

    Kemungkinan sampai disini sinyal juga sudah cukup halus
    untuk dicari puncak2nya.

    flag , 0 artinya awal mencari
    > 0, artinya cari yang maksimum
    < 0, artinya cari yang minimum

*/
int hitung_fase_pickup(double *in, int awal, int akhir, int len, int flag)
{
    int i;
    int x_max, x_min;

    /* cari dulu posisi maksimum dari sinyal */
    double max, min;
    max = -4000000000.00;
    min = 4000000000.00;

    if (awal < 0) return 0;
    if (akhir > len) return 0;

    /* loop awal untuk mencari nilai pertama maksimum */
    if (flag == 0)
    {
        for (i= awal; i<akhir; i++)
        {
            if (in[i] > max)
            {
                max = in[i];
                x_max = i;
            }

            if (in[i] < min)
            {
                min = in[i];
                x_min = i;
            }
        }

        //printf("len %d: maks %d, %f, min %d, %f\n", pos_pickup, x_max, max, x_min, min);

        if (fabs(min) > fabs(max))
        {
            return -x_min;  /* return negatif, ingat nanti difabs di penerimanya */
        }
        else
            return x_max;
    }

    if (flag > 0)
    {
        for (i= awal; i<akhir; i++)
        {
            if (in[i] > max)
            {
                max = in[i];
                x_max = i;
            }
        }

        return x_max;
    }

    if (flag < 0)
    {
        for (i= awal; i<akhir; i++)
        {
            if (in[i] < min)
            {
                min = in[i];
                x_min = i;
            }
        }

        return x_min;
    }

}

/* menghitung rata2 fase, sambil mendeteksi valid atau tidaknya */
double rata_fase(double *in, int len)
{
    int i;
    int j = 0;

    double tot = 0;

    for (i=0 ; i<len; i++)
    {
        if ( in[i] > 0)
        {
            j++;
            tot += in[i];
        }
    }

    return (double) ( tot/ j);
}

double rata_fase_antar_ch(double *in, int len)
{
    int i;
    int j = 0;

    double tot = 0;

    for (i=0 ; i<len; i++)
    {
        if (in[i] < -360 ) continue;
        if (in[i] > 360  ) continue;
        if (in[i] == 0) continue;
        {
            j++;
            tot += in[i];
        }
    }

    return (double) ( tot/ j);
}

/*  mencari trigger dari data pulsa yang masuk

    jika pulsa dari kaki 4 (4N35) yang disambungkan dengan
    kanal 4 ground input.

    Kita cari mulai falling, dengan cara mencari turunan tertinggi

    return 0, jika gak dpt yang valid
    return 1, jika valid
*/
static double *temp_buf;
#define treshold 0.5

int cari_trigger_dari_pulsa(double *in, int len, int *trig, int *len_360, int *len_720)
{
    /* jika ini yang pertama maka init temp buffer dulu */
    if (temp_buf == 0)
        temp_buf = malloc (sizeof (double) * SAMPLE_PER_SIKLUS + 512 );

    int i;
    int flag_max1 = 0;
    int flag_max2 = 0;
    int flag_max3 = 0;
    int pos_max1;
    int pos_max2;
    int pos_max3;
    double tt = -0.1;   /*AKTIF LOW : sesuai dengan treshold yang diset, juga mau aktif low atau high */

    for (i=0; i<len; i++)
    {
        temp_buf[i] = in[i+1]-in[i];

#if 1
        if ( flag_max1 == 0 )
        {
            if ( temp_buf[i] < tt )
            {
                flag_max1 = 1;
                //printf("Dapat di %d, %f\r\n", i, temp_buf[i]);
                pos_max1 = i;
                i += 10;    /* biar tidak terlalu mepet */

                continue; /* lanjut loop */
            }
        }

        if (flag_max2 == 0)
        {
            if (flag_max1 == 1)
            {
                if ( temp_buf[i] < tt )
                {
                    flag_max2 = 1;
                    pos_max2 = i;
                    //printf("Dapat 2 di %d, %f\r\n", i, temp_buf[i]);
                    //printf(" pjg  = %d\r\n", (pos_max2 - pos_max1));

                    if ( pos_max2 - pos_max1 > 100 )
                    {
                        *trig = pos_max1;
                        *len_360 = (pos_max2 - pos_max1);

                        return 1;
                    }
                    return 0;
                }
            }
        }
#endif
    }

    /* jika sampai disini berarti tidak ketemu pulsanya */
    return 0;

    for (i=0; i<len; i++)
    {
        in[i] = temp_buf[i];
    }

    in[ len - 1] = in[0];

}


/* dicopy dari rtc.c Haliza versi blackfin

    Des 2014
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <linux/rtc.h>


static unsigned char tk[64];
static unsigned char th[64];
static unsigned char bulan[32];

char *get_jam(void)
{
    time_t curtime;
    struct rtc_time tmku;

    /* Get the current time. */
    curtime = time (NULL);
    rtc_time_to_tm( curtime, &tmku);

    sprintf(tk, "%02d:%02d:%02d", tmku.tm_hour, tmku.tm_min, tmku.tm_sec);

    return tk;
}

char *get_tahun(void)
{
    time_t tim;
    struct rtc_time tmku;

    //tim = rtc_bfin_to_time(1);
    tim = time (NULL);
    rtc_time_to_tm(tim, &tmku);

    if (tmku.tm_mon == 0)
    {
        sprintf(bulan, "Jan");
    }
    else if (tmku.tm_mon == 1)
    {
        sprintf(bulan, "Feb");
    }
    else if (tmku.tm_mon == 2)
    {
        sprintf(bulan, "Mar");
    }
    else if (tmku.tm_mon == 3)
    {
        sprintf(bulan, "Apr");
    }
    else if (tmku.tm_mon == 4)
    {
        sprintf(bulan, "Mei");
    }
    else if (tmku.tm_mon == 5)
    {
        sprintf(bulan, "Jun");
    }
    else if (tmku.tm_mon == 6)
    {
        sprintf(bulan, "Jul");
    }
    else if (tmku.tm_mon == 7)
    {
        sprintf(bulan, "Agt");
    }
    else if (tmku.tm_mon == 8)
    {
        sprintf(bulan, "Sep");
    }
    else if (tmku.tm_mon == 9)
    {
        sprintf(bulan, "Okt");
    }
    else if (tmku.tm_mon == 10)
    {
        sprintf(bulan, "Nov");
    }
    else if (tmku.tm_mon == 11)
    {
        sprintf(bulan, "Des");
    }

    sprintf(th, "%02d %s %02d", tmku.tm_mday, bulan, (1900+tmku.tm_year));
    return th;
}

char *get_tahun_tim( unsigned long tim )
{
    struct rtc_time tmku;

    rtc_time_to_tm( (time_t) tim, &tmku);

    if (tmku.tm_mon == 0)
    {
        sprintf(bulan, "Jan");
    }
    else if (tmku.tm_mon == 1)
    {
        sprintf(bulan, "Feb");
    }
    else if (tmku.tm_mon == 2)
    {
        sprintf(bulan, "Mar");
    }
    else if (tmku.tm_mon == 3)
    {
        sprintf(bulan, "Apr");
    }
    else if (tmku.tm_mon == 4)
    {
        sprintf(bulan, "Mei");
    }
    else if (tmku.tm_mon == 5)
    {
        sprintf(bulan, "Jun");
    }
    else if (tmku.tm_mon == 6)
    {
        sprintf(bulan, "Jul");
    }
    else if (tmku.tm_mon == 7)
    {
        sprintf(bulan, "Agt");
    }
    else if (tmku.tm_mon == 8)
    {
        sprintf(bulan, "Sep");
    }
    else if (tmku.tm_mon == 9)
    {
        sprintf(bulan, "Okt");
    }
    else if (tmku.tm_mon == 10)
    {
        sprintf(bulan, "Nov");
    }
    else if (tmku.tm_mon == 11)
    {
        sprintf(bulan, "Des");
    }

    sprintf(th, "%02d %s %02d", tmku.tm_mday, bulan, (1900+tmku.tm_year));
    return th;
}

char *get_jam_tim( unsigned long tim)
{
    struct rtc_time tmku;

    rtc_time_to_tm(tim, &tmku);

    sprintf(tk, "%02d:%02d:%02d", tmku.tm_hour, tmku.tm_min, tmku.tm_sec);

    return tk;
}
