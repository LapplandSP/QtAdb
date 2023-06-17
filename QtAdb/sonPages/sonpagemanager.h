#ifndef SONPAGEMANAGER_H
#define SONPAGEMANAGER_H

#include <QApplication>
#include "adbprocess.h"
#include "textexplainer.h"
#include "devInfo/sp_dpichanger.h"
#include "devInfo/sp_wmsize.h"
#include "activator/sp_activator.h"
#include "apps/sp_installer.h"
#include "apps/sp_permissiongroups.h"
#include "apps/sp_permissions.h"
#include "apps/sp_packages.h"
#include "apps/sp_features.h"
#include "apps/sp_libraries.h"
#include "apps/sp_users.h"
#include "devControl/sp_devcontrol_power.h"
#include "devControl/btnemulator.h"
#include "recovery/sp_recovery.h"
#include "advanced/sp_customize_cmd.h"
#include "advanced/sp_accounts.h"
#include "advanced/sp_captive_portal.h"
#include "advanced/sp_scales.h"
#include "advanced/sp_status_bar.h"
#include "advanced/sp_vibrate.h"


class sonPageManager
{
public:
    sonPageManager();
    ~sonPageManager();

    adbProcess *process;
    textExplainer *explainer;


    animationWidget *selector(QWidget *parent, QString parentName, int key , device dev);

private:

    animationWidget* createSonPageFor_devInfo(QWidget *parent, int key, device dev);
    animationWidget* createSonPageFor_activator(QWidget *parent, int key, device dev);
    animationWidget* createSonPageFor_apps(QWidget *parent, int key, device dev);
    animationWidget* createSonPageFor_devControl(QWidget *parent, int key, device dev);
    animationWidget* createSonPageFor_recovery(QWidget *parent, int key, device dev);
    animationWidget* createSonPageFor_advanced(QWidget *parent, int key, device dev);
};

#endif // SONPAGEMANAGER_H
