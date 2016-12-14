#-------------------------------------------------
#
# Project created by QtCreator 2016-12-04T20:29:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LAT_DSP
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    util/dsp.cpp \
    util/fourierd.c \
    util/fourierf.c \
    util/fftmisc.c
#    util/window_filter.c \
#    util/utils.c


HEADERS  += mainwindow.h \
    util/dsp.h \
    util/fourier.h \
    util/ddcmath.h \
#    util/window_filter.h \
#    util/utils.h


FORMS    += mainwindow.ui

INCLUDEPATH += /home/jono/KANTOR/koding/daunbiru/haliza/qt_lib/qwt-6.1.3/src
LIBS += -L/home/jono/KANTOR/koding/daunbiru/haliza/qt_lib/lib_qwt-6.1.3/lib -lqwt -lm
