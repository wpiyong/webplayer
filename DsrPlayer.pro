#-------------------------------------------------
#
# Project created by QtCreator 2018-04-05T12:19:12
#
#-------------------------------------------------

QT       += opengl
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DsrPlayer
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

LIBS += -L/home/dev03/DSR/WebAssembly/qtbase-webassembly/plugins/imageformats -lqgif -lqico -lqjpeg
#LIBS += -L/home/dev03/DSR/WebAssembly/qtbase-webassembly/plugins/sqldrivers -lqsqlite

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    gl/glwidget.cpp \
    widgets/imageviewerwidget.cpp \
    lib/apiservices.cpp \
    controllers/dsrplayercontroller.cpp \
    lib/models/apimodel.cpp \
    lib/models/revolution.cpp \
    lib/models/revolutionset.cpp \
    lib/models/info/accountapiinfo.cpp \
    lib/models/info/apiinfo.cpp \
    lib/models/info/deviceapiinfo.cpp \
    lib/models/sessions/apisession.cpp \
    lib/models/sessions/clientapisession.cpp \
    lib/models/sessions/deviceapisession.cpp \
    lib/models/sessions/userapisession.cpp \
    lib/models/users/dsraccountmember.cpp \
    lib/models/users/dsrenduser.cpp \
    lib/models/users/dsruser.cpp \
    lib/models/apimodel.cpp \
    lib/models/revolution.cpp \
    lib/models/revolutionset.cpp \
    lib/models/camera_systems/camerasystem.cpp \
    lib/models/camera_systems/dsre.cpp \
    lib/models/info/accountapiinfo.cpp \
    lib/models/info/apiinfo.cpp \
    lib/models/info/deviceapiinfo.cpp \
    lib/models/sessions/apisession.cpp \
    lib/models/sessions/clientapisession.cpp \
    lib/models/sessions/deviceapisession.cpp \
    lib/models/sessions/userapisession.cpp \
    lib/models/users/dsraccountmember.cpp \
    lib/models/users/dsrenduser.cpp \
    lib/models/users/dsruser.cpp \
    lib/models/apimodel.cpp \
    lib/models/revolution.cpp \
    lib/models/revolutionset.cpp \
    lib/tasks/revolutiondownloadtask.cpp \
    lib/downloadmanager.cpp \
    lib/jstoc.c \
    lib/base64.c

HEADERS += \
        mainwindow.h \
    gl/glwidget.h \
    widgets/imageviewerwidget.h \
    lib/apiservices.h \
    controllers/dsrplayercontroller.h \
    lib/models/revolutionset.h \
    lib/models/revolution.h \
    lib/models/apimodel.h \
    lib/models/info/accountapiinfo.h \
    lib/models/info/apiinfo.h \
    lib/models/info/deviceapiinfo.h \
    lib/models/sessions/apisession.h \
    lib/models/sessions/clientapisession.h \
    lib/models/sessions/deviceapisession.h \
    lib/models/sessions/userapisession.h \
    lib/models/users/dsraccountmember.h \
    lib/models/users/dsrenduser.h \
    lib/models/users/dsruser.h \
    lib/models/apimodel.h \
    lib/models/revolution.h \
    lib/models/revolutionset.h \
    lib/models/camera_systems/camerasystem.h \
    lib/models/camera_systems/dsre.h \
    lib/models/info/accountapiinfo.h \
    lib/models/info/apiinfo.h \
    lib/models/info/deviceapiinfo.h \
    lib/models/sessions/apisession.h \
    lib/models/sessions/clientapisession.h \
    lib/models/sessions/deviceapisession.h \
    lib/models/sessions/userapisession.h \
    lib/models/users/dsraccountmember.h \
    lib/models/users/dsrenduser.h \
    lib/models/users/dsruser.h \
    lib/models/apimodel.h \
    lib/models/revolution.h \
    lib/models/revolutionset.h \
    lib/tasks/revolutiondownloadtask.h \
    lib/downloadmanager.h \
    lib/emprintf.h \
    lib/jstoc.h

RESOURCES += \
    images/images.qrc
