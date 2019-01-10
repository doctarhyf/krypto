#-------------------------------------------------
#
# Project created by QtCreator 2019-01-05T21:38:58
#
#-------------------------------------------------

QT       += core gui winextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = krypto
TEMPLATE = app


SOURCES += main.cpp \
    #widgetProgramsList.cpp \
    formlogin.cpp \
    formmain.cpp \
    formusers.cpp \
    formprogramslist.cpp \
    dialogaddprogram.cpp \
    dialogadduser.cpp \
    logger.cpp

HEADERS  += \
    #widgetProgramsList.h \
    formlogin.h \
    formmain.h \
    formusers.h \
    formprogramslist.h \
    dialogaddprogram.h \
    dialogadduser.h \
    logger.h

FORMS    += \
    #widgetProgramsList.ui \
    formlogin.ui \
    formmain.ui \
    formusers.ui \
    formprogramslist.ui \
    dialogaddprogram.ui \
    dialogadduser.ui

RESOURCES += \
    res.qrc

RC_FILE = myrc.rc
