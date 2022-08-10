QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    adbprocess.cpp \
    animationwidget.cpp \
    basepage.cpp \
    indexlistitem.cpp \
    main.cpp \
    mainwindow.cpp \
    pagelistitem.cpp \
    pagemaker.cpp \
    sonPages/activator/sp_activator.cpp \
    sonPages/advanced/sp_customize_cmd.cpp \
    sonPages/apps/sp_installer.cpp \
    sonPages/devControl/btnemulator.cpp \
    sonPages/devControl/sp_devcontrol_power.cpp \
    sonPages/devInfo/sp_dpichanger.cpp \
    sonPages/pay.cpp \
    sonPages/recovery/sp_recovery.cpp \
    sonPages/sonpagebase.cpp \
    sonPages/sonpagemanager.cpp \
    sonPages/standardoutputpage.cpp \
    textexplainer.cpp \
    threads/adbthread.cpp \
    threads/thread_createpage.cpp \
    welcomepage.cpp

HEADERS += \
    about.h \
    adbprocess.h \
    animationwidget.h \
    basepage.h \
    indexlistitem.h \
    mainwindow.h \
    pagelistitem.h \
    pagemaker.h \
    sonPages/activator/sp_activator.h \
    sonPages/advanced/sp_customize_cmd.h \
    sonPages/apps/sp_installer.h \
    sonPages/devControl/btnemulator.h \
    sonPages/devControl/sp_devcontrol_power.h \
    sonPages/devInfo/sp_dpichanger.h \
    sonPages/pay.h \
    sonPages/recovery/sp_recovery.h \
    sonPages/sonpagebase.h \
    sonPages/sonpagemanager.h \
    sonPages/standardoutputpage.h \
    textexplainer.h \
    threads/adbthread.h \
    threads/thread_createpage.h \
    welcomepage.h

FORMS += \
    about.ui \
    basepage.ui \
    indexlistitem.ui \
    mainwindow.ui \
    pagelistitem.ui \
    sonPages/activator/sp_activator.ui \
    sonPages/advanced/sp_customize_cmd.ui \
    sonPages/apps/sp_installer.ui \
    sonPages/devControl/btnemulator.ui \
    sonPages/devControl/sp_devcontrol_power.ui \
    sonPages/devInfo/sp_dpichanger.ui \
    sonPages/pay.ui \
    sonPages/recovery/sp_recovery.ui \
    sonPages/sonpagebase.ui \
    sonPages/standardoutputpage.ui \
    welcomepage.ui

TRANSLATIONS += \
    QtAdb_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ico.qrc

RC_FILE += logo.rc
