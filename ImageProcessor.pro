#-------------------------------------------------
#
# Project created by QtCreator 2015-08-03T18:27:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = ImageProcessor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imageprocessor.cpp \
    image.cpp \
    imagewindow.cpp \
    scalingwindow.cpp \
    bcadjustmentwindow.cpp \
    qcustomplot.cpp \
    histogram.cpp

HEADERS  += mainwindow.h \
    imageprocessor.h \
    image.h \
    imagewindow.h \
    scalingwindow.h \
    bcadjustmentwindow.h \
    qcustomplot.h \
    histogram.h

FORMS    += mainwindow.ui \
    scalingwindow.ui \
    bcadjustmentwindow.ui \
    histogram.ui

RESOURCES += \
    resourses/r.qrc
