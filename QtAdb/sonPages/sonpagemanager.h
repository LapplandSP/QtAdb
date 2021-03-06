#ifndef SONPAGEMANAGER_H
#define SONPAGEMANAGER_H

#include "adbprocess.h"
#include "textexplainer.h"
#include "devInfo/sp_dpichanger.h"
#include "activator/sp_activator.h"
#include "apps/sp_installer.h"
#include "devControl/sp_devcontrol_power.h"
#include "devControl/btnemulator.h"
#include "recovery/sp_recovery.h"


class sonPageManager
{
public:
    sonPageManager();

    adbProcess *process;
    textExplainer *explainer;


    QWidget *selector(QWidget *parent, QString parentName, int key , device dev);

private:

    sp_dpiChanger* createSonPageFor_devInfo(QWidget *parent, int key, device dev);
    sp_activator* createSonPageFor_activator(QWidget *parent, int key, device dev);
    sp_installer* createSonPageFor_apps(QWidget *parent, int key, device dev);
    QWidget* createSonPageFor_devControl(QWidget *parent, int key, device dev);
    QWidget* createSonPageFor_recovery(QWidget *parent, int key, device dev);
};

#endif // SONPAGEMANAGER_H
