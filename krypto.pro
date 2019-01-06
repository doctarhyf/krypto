#-------------------------------------------------
#
# Project created by QtCreator 2019-01-05T21:38:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = krypto
TEMPLATE = app


SOURCES += main.cpp \
    widgetProgramsList.cpp \
    formlogin.cpp \
    formmain.cpp

HEADERS  += \
    widgetProgramsList.h \
    formlogin.h \
    formmain.h

FORMS    += \
    widgetProgramsList.ui \
    formlogin.ui \
    formmain.ui

RESOURCES += \
    res.qrc
