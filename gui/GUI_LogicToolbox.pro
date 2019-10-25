#-------------------------------------------------
#
# Project created Alma Ibrasimovic
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4):

QT += widgets

TARGET = GUI_LogicToolbox
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        cvor.cpp \
        grana.cpp \
        graphwidget.cpp

HEADERS += \
        mainwindow.h \
        cvor.h \
        grana.h \
        graphwidget.h

FORMS += \
        mainwindow.ui


LIBS += -L$$PWD/../../../../../usr/lib/ -lcdt
LIBS += -L$$PWD/../../../../../usr/lib/ -lcgraph
LIBS += -L$$PWD/../../../../../usr/lib/ -lgvc
LIBS += -L$$PWD/../../../../../usr/lib/ -lpathplan


unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/lib/ -llogictoolbox

INCLUDEPATH += $$PWD/../../../../../usr/local/include/logictoolbox
DEPENDPATH += $$PWD/../../../../../usr/local/include/logictoolbox

