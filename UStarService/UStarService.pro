#-------------------------------------------------
#
# Project created by QtCreator 2020-11-27T10:05:08
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UStarService
TEMPLATE = app


SOURCES += main.cpp\
    gridline.cpp \
    loginform.cpp \
    robot.cpp \
    mainwindow.cpp

HEADERS  += \
    gridline.h \
    loginform.h \
    robot.h \
    mianwindow.h

FORMS    +=

RESOURCES += \
    resource.qrc

DISTFILES +=
