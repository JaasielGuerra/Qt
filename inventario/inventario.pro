#-------------------------------------------------
#
# Project created by QtCreator 2015-06-03T13:06:24
#
#-------------------------------------------------

QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = inventario
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    inventario.cpp \
    createuser.cpp \
    users.cpp \
    inventariover.cpp \
    menumain.cpp \
    about.cpp \
    dot.cpp

HEADERS  += mainwindow.h \
    inventario.h \
    createuser.h \
    users.h \
    inventariover.h \
    dbconnect.h \
    menumain.h \
    about.h \
    cifrado.h \
    dot.h

FORMS    += mainwindow.ui \
    inventario.ui \
    createuser.ui \
    users.ui \
    inventariover.ui \
    menumain.ui \
    about.ui \
    dot.ui
