QT       += core gui
QT += serialport
QT += core5compat
# QMAKE_LFLAGS += /MANIFESTUAC:\"level=\'requireAdministrator\' uiAccess=\'false\'\"

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    abstract/comboboxlistwidget.cpp \
    adbprocess.cpp \
    animationwidget.cpp \
    basepage.cpp \
    devitem.cpp \
    indexlistitem.cpp \
    main.cpp \
    mainwindow.cpp \
    monitor.cpp \
    pagelistitem.cpp \
    pagemaker.cpp \
    sonPages/activator/sp_activator.cpp \
    sonPages/advanced/sp_accounts.cpp \
    sonPages/advanced/sp_captive_portal.cpp \
    sonPages/advanced/sp_customize_cmd.cpp \
    sonPages/advanced/sp_scales.cpp \
    sonPages/advanced/sp_status_bar.cpp \
    sonPages/apps/sp_features.cpp \
    sonPages/apps/sp_installer.cpp \
    sonPages/apps/sp_libraries.cpp \
    sonPages/apps/sp_packages.cpp \
    sonPages/apps/sp_permissiongroups.cpp \
    sonPages/apps/sp_permissions.cpp \
    sonPages/apps/sp_users.cpp \
    sonPages/apps/tp_packageprofile.cpp \
    sonPages/devControl/btnemulator.cpp \
    sonPages/devControl/sp_devcontrol_power.cpp \
    sonPages/devInfo/sp_dpichanger.cpp \
    sonPages/devInfo/sp_wmsize.cpp \
    sonPages/links.cpp \
    sonPages/pay.cpp \
    sonPages/recovery/sp_recovery.cpp \
    sonPages/sonpagebase.cpp \
    sonPages/sonpagemanager.cpp \
    sonPages/standardoutputpage.cpp \
    textexplainer.cpp \
    threads/adbthread.cpp \
    threads/thread_createpage.cpp \
    threads/thread_monitor.cpp \
    usb_listener.cpp \
    welcomepage.cpp

HEADERS += \
    about.h \
    abstract/comboboxlistwidget.h \
    adbprocess.h \
    animationwidget.h \
    basepage.h \
    devitem.h \
    indexlistitem.h \
    mainwindow.h \
    monitor.h \
    pagelistitem.h \
    pagemaker.h \
    sonPages/activator/sp_activator.h \
    sonPages/advanced/sp_accounts.h \
    sonPages/advanced/sp_captive_portal.h \
    sonPages/advanced/sp_customize_cmd.h \
    sonPages/advanced/sp_scales.h \
    sonPages/advanced/sp_status_bar.h \
    sonPages/apps/sp_features.h \
    sonPages/apps/sp_installer.h \
    sonPages/apps/sp_libraries.h \
    sonPages/apps/sp_packages.h \
    sonPages/apps/sp_permissiongroups.h \
    sonPages/apps/sp_permissions.h \
    sonPages/apps/sp_users.h \
    sonPages/apps/tp_packageprofile.h \
    sonPages/devControl/btnemulator.h \
    sonPages/devControl/sp_devcontrol_power.h \
    sonPages/devInfo/sp_dpichanger.h \
    sonPages/devInfo/sp_wmsize.h \
    sonPages/links.h \
    sonPages/pay.h \
    sonPages/recovery/sp_recovery.h \
    sonPages/sonpagebase.h \
    sonPages/sonpagemanager.h \
    sonPages/standardoutputpage.h \
    textexplainer.h \
    threads/adbthread.h \
    threads/thread_createpage.h \
    threads/thread_monitor.h \
    usb_listener.h \
    welcomepage.h

FORMS += \
    about.ui \
    basepage.ui \
    devitem.ui \
    indexlistitem.ui \
    mainwindow.ui \
    monitor.ui \
    pagelistitem.ui \
    sonPages/activator/sp_activator.ui \
    sonPages/advanced/sp_accounts.ui \
    sonPages/advanced/sp_captive_portal.ui \
    sonPages/advanced/sp_customize_cmd.ui \
    sonPages/advanced/sp_scales.ui \
    sonPages/advanced/sp_status_bar.ui \
    sonPages/apps/sp_features.ui \
    sonPages/apps/sp_installer.ui \
    sonPages/apps/sp_libraries.ui \
    sonPages/apps/sp_packages.ui \
    sonPages/apps/sp_permissiongroups.ui \
    sonPages/apps/sp_permissions.ui \
    sonPages/apps/sp_users.ui \
    sonPages/apps/tp_packageprofile.ui \
    sonPages/devControl/btnemulator.ui \
    sonPages/devControl/sp_devcontrol_power.ui \
    sonPages/devInfo/sp_dpichanger.ui \
    sonPages/devInfo/sp_wmsize.ui \
    sonPages/links.ui \
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
    cfgs.qrc \
    ico.qrc \
    styles.qrc

RC_FILE += logo.rc
