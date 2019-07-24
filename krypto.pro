#-------------------------------------------------
#
# Project created by QtCreator 2019-01-05T21:38:58
#
#-------------------------------------------------

QT       += core gui
#winextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = krypto
TEMPLATE = app



SOURCES += main.cpp \
    formlogin.cpp \
    formmain.cpp \
    formusers.cpp \
    formprogramslist.cpp \
    dialogaddprogram.cpp \
    logger.cpp

HEADERS  += \
    formlogin.h \
    formmain.h \
    formusers.h \
    formprogramslist.h \
    dialogaddprogram.h \
    logger.h

FORMS    += \
    formlogin.ui \
    formmain.ui \
    formusers.ui \
    formprogramslist.ui \
    dialogaddprogram.ui

RESOURCES += \
    res.qrc

RC_FILE = myrc.rc

TRANSLATIONS = krypto_fr.ts \
                 krypto_ch.ts
