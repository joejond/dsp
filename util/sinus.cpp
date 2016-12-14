#include "sinus.h"
#include <QDebug>

sinus::sinus(double *sinus, double amp)
{
    int i;
    for(i=0;i<512,i++){
        sinus[i] = i * 100;
    }

}

sinus::test(){
    qDebug() << "Taraaaaa. akhirnya masuk juga";
}
