#include "time_t.h"
#include "qmainwindow.h"
#include "mainwindow.h"
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QTime>
#include <QString>

time_tt::time_tt(QThread *parent) :
    QThread(parent)
{
    QTimer *timerr = new QTimer(this);
    connect(timerr, SIGNAL(timeout()), this, SLOT(run()));
    timerr->start(500);
}

void time_tt::run() {
    this->waktu = QTime::currentTime();
    this->simpanWaktu(this->waktu.toString("hh:mm:ss"));
}

QString time_tt::bacaWaktu() {
    return this->data_waktu; //just comment
}

void time_tt::simpanWaktu(QString timee) {
    this->data_waktu = timee;
}
