#-------------------------------------------------
#
# Project created by QtCreator 2019-11-16T18:44:53
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = eshmgr
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

CONFIG += c++11

SOURCES += \
        action_view.cpp \
        actions.cpp \
        actions_list.cpp \
        eshimapi.cpp \
        gettoken.cpp \
        main.cpp \
        login.cpp \
        mainmenu.cpp \
        stats.cpp \
        value_view.cpp \
        values_list.cpp

HEADERS += \
        action_view.h \
        actions.h \
        actions_list.h \
        eshimapi.h \
        gettoken.h \
        login.h \
        mainmenu.h \
        stats.h \
        value_view.h \
        values_list.h

FORMS += \
        action_view.ui \
        actions_list.ui \
        login.ui \
        mainmenu.ui \
        stats.ui \
        value_view.ui \
        values_list.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
