QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += QT_NO_DEPRECATED_WARNINGS

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    console.cpp \
    externalcommand.cpp \
    formatmanager.cpp \
    internalcommand.cpp \
    main.cpp \
    mainwindow.cpp \
    tokenizer.cpp

HEADERS += \
    common.h \
    console.h \
    environment.h \
    externalcommand.h \
    formatmanager.h \
    icommandstrategy.h \
    internalcommand.h \
    internalenvironment.h \
    mainwindow.h \
    tokenizer.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rsc.qrc

RC_FILE = icon.rc

DESTDIR += $$PWD
