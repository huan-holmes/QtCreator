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
    mainwindow.cpp \
    paint.cpp \
    operationwidget.cpp \
    mappingwidget.cpp \
    virtualwalldockwidget.cpp \
    videodockwidget.cpp

HEADERS  += \
    gridline.h \
    loginform.h \
    robot.h \
    mianwindow.h \
    paint.h \
    operationwidget.h \
    mappingwidget.h \
    virtualwalldockwidget.h \
    videodockwidget.h

FORMS    +=

RESOURCES += \
    resource.qrc

DISTFILES +=

INCLUDEPATH += .
INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/local/include/opencv
INCLUDEPATH += /usr/local/include/opencv2
LIBS += -L/usr/local/lib/ -lopencv_core -lopencv_highgui -lopencv_imgproc
