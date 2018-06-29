#-------------------------------------------------
#
# Project created by QtCreator 2018-06-27T12:50:39
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BotBittrex
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
    jbittrex.cpp \
    JBittrex/jbalance.cpp \
    JBittrex/jcurrency.cpp \
    JBittrex/jmarket.cpp \
    JBittrex/jopenedorder.cpp \
    JBittrex/jtickers.cpp \
    jlistmodelbalances.cpp \
    jlistmodelevents.cpp \
    jsellorder.cpp \
    jlistmodelopenorders.cpp

HEADERS += \
        mainwindow.h \
    jbittrex.h \
    JBittrex/jbalance.h \
    JBittrex/jcurrency.h \
    JBittrex/jmarket.h \
    JBittrex/jopenedorder.h \
    JBittrex/jtickers.h \
    jlistmodelbalances.h \
    jlistmodelevents.h \
    jsellorder.h \
    jlistmodelopenorders.h

FORMS += \
        mainwindow.ui
