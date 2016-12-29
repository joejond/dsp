#ifndef TIME_TT_H
#define TIME_TT_H

#include <QObject>
#include <QThread>
#include <QTime>
#include <QString>

//extern QString nilaiiii;

class time_tt : public QThread
{
    Q_OBJECT
public:
    QTime waktu;
    QString data_waktu;
    QString bacaWaktu();
    void simpanWaktu(QString data);
    //const char str;
    explicit time_tt(QThread *parent = 0);

public slots:
    void run();

signals:

};

#endif // TIME_TT_H
