#-------------------------------------------------
#
# Project created by QtCreator 2018-09-28T08:37:50
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += multimedia
QT += multimediawidgets
QT += multimedia
TARGET = centralKiosk
TEMPLATE = app

QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig debug
PKGCONFIG += mpv

SOURCES += main.cpp \
    mpvwidget.cpp \
    touchscreen.cpp \
    ledscreen.cpp \
    tcpsocketserver.cpp \
    alphaVideoPlayer.cpp \
    videoplayer.cpp \
    udpserver.cpp


HEADERS  += \
    mpvwidget.h \
    alphaVideoPlayer \
    touchscreen.h \
    ledscreen.h \
    tcpsocketserver.h \
    mpv_qt_helper.h \
    alphaVideoPlayer.h \
    videoplayer.h \
    udpserver.h \
    msgdef.h


FORMS    +=


LIBS+=
