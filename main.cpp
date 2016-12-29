#include "mainwindow.h"
#include <QApplication>
#include "time_t.h"
#include <QTimer>
#include <QMainWindow>
#include <QThread>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    time_tt waktu;
    waktu.run();
//    w.setFixedSize(1024,700);
    w.show();

    return a.exec();
}
