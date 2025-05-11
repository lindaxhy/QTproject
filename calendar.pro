QT       += core gui
QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cal_login.cpp \
    city.cpp \
    color_mode.cpp \
    everyday_sentence.cpp \
    main.cpp \
    mainwindow.cpp \
    reg.cpp \
    text_mode.cpp

HEADERS += \
    cal_login.h \
    city.h \
    color_mode.h \
    everyday_sentence.h \
    mainwindow.h \
    reg.h \
    text_mode.h

FORMS += \
    cal_login.ui \
    city.ui \
    color_mode.ui \
    everyday_sentence.ui \
    mainwindow.ui \
    reg.ui \
    text_mode.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
